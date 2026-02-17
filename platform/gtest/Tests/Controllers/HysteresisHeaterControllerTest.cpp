#include "application/System/Controllers/HeaterController/HysteresisHeaterController/HysteresisHeaterController.hpp"

#include "application/System/Controllers/PersistentStorageController/PersistentData/HeaterPersistentConfig.hpp"
#include "platform/gtest/Mocks/Controllers/LoggerSinkMock.hpp"
#include "platform/gtest/Mocks/Drivers/OutputSwitchMock.hpp"
#include "platform/gtest/Mocks/Drivers/TemperatureSensorMock.hpp"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

using namespace testing;

namespace ATC {
class HysteresisHeaterControllerTest : public Test {
public:
    static constexpr HeaterPersistentConfig HEATER_PERSISTENT_CONFIG {
        .targetTemperatureInCelsius = 250
    };

    static constexpr float ROOM_TEMPERATURE_IN_CELSIUS = 24.7F;
    static constexpr uint8_t TICKS_AMOUNT = 5;
    static constexpr float TEMPERATURE_STEP = 9.8F;

    LoggerSinkMock loggerSinkMock_ {};
    OutputSwitchMock heaterSwitchMock_ {};
    TemperatureSensorMock temperatureSensorMock_ {};
    static constexpr float HYSTERESIS_MARGIN_IN_CELSIUS = 1;

    HysteresisHeaterController hysteresisHeaterController_ {
        loggerSinkMock_,
        heaterSwitchMock_,
        temperatureSensorMock_,
        HYSTERESIS_MARGIN_IN_CELSIUS
    };
};

TEST_F(
    HysteresisHeaterControllerTest,
    GIVEN_hysteresisHeaterController_WHEN_controllerIsInitialized_THEN_heaterSwitchIsSetUp
) {
    {
        InSequence sequence;

        EXPECT_CALL(heaterSwitchMock_, init());
        EXPECT_CALL(heaterSwitchMock_, turnOff());
    }

    hysteresisHeaterController_.init(HEATER_PERSISTENT_CONFIG);
}

TEST_F(
    HysteresisHeaterControllerTest,
    GIVEN_hysteresisHeaterController_WHEN_controllerIsInitialized_THEN_temperatureSensorIsSetUp
) {
    EXPECT_CALL(temperatureSensorMock_, init());

    hysteresisHeaterController_.init(HEATER_PERSISTENT_CONFIG);
}

TEST_F(
    HysteresisHeaterControllerTest,
    GIVEN_hysteresisHeaterController_WHEN_heaterIsTooCold_THEN_heaterIsHeatUp
) {
    hysteresisHeaterController_.init(HEATER_PERSISTENT_CONFIG);
    hysteresisHeaterController_.turnOn();

    {
        InSequence sequence;

        EXPECT_CALL(heaterSwitchMock_, turnOn()).Times(AtLeast(1));

        constexpr float startTemperature = ROOM_TEMPERATURE_IN_CELSIUS;
        constexpr float endTemperature =
            HEATER_PERSISTENT_CONFIG.targetTemperatureInCelsius -
            TEMPERATURE_STEP;

        for (float temperature = startTemperature;
             temperature < endTemperature;
             temperature += TEMPERATURE_STEP) {
            ON_CALL(temperatureSensorMock_, getCelsius())
                .WillByDefault(Return(temperature));

            hysteresisHeaterController_.tick();
        }
    }
}

TEST_F(
    HysteresisHeaterControllerTest,
    GIVEN_hysteresisHeaterController_WHEN_heaterIsTooHot_THEN_heaterIsHeatUp
) {
    hysteresisHeaterController_.init(HEATER_PERSISTENT_CONFIG);
    hysteresisHeaterController_.turnOn();

    {
        InSequence sequence;

        EXPECT_CALL(heaterSwitchMock_, turnOff()).Times(AtLeast(1));

        constexpr float startTemperature =
            HEATER_PERSISTENT_CONFIG.targetTemperatureInCelsius + 100;

        constexpr float endTemperature =
            HEATER_PERSISTENT_CONFIG.targetTemperatureInCelsius +
            TEMPERATURE_STEP;

        for (float temperature = startTemperature;
             temperature > endTemperature;
             temperature -= TEMPERATURE_STEP) {
            ON_CALL(temperatureSensorMock_, getCelsius())
                .WillByDefault(Return(temperature));

            hysteresisHeaterController_.tick();
        }
    }
}

TEST_F(
    HysteresisHeaterControllerTest,
    GIVEN_hysteresisHeaterController_WHEN_setTargetTemperatureIsCalled_THEN_targetTemperatureIsSet
) {
    hysteresisHeaterController_.init(HEATER_PERSISTENT_CONFIG);
    ASSERT_EQ(
        hysteresisHeaterController_.getTargetTemperatureInCelsius(),
        HEATER_PERSISTENT_CONFIG.targetTemperatureInCelsius
    );
    constexpr float newTemperature =
        HEATER_PERSISTENT_CONFIG.targetTemperatureInCelsius + 100;

    hysteresisHeaterController_.setTargetTemperatureInCelsius(
        newTemperature
    );

    ASSERT_EQ(
        hysteresisHeaterController_.getTargetTemperatureInCelsius(),
        newTemperature
    );
}

TEST_F(
    HysteresisHeaterControllerTest,
    GIVEN_hysteresisHeaterController_WHEN_setTargetTemperatureIsCalledWithIncorrectValue_THEN_errorIsLogged
) {
    hysteresisHeaterController_.init(HEATER_PERSISTENT_CONFIG);

    constexpr float newTemperature = HYSTERESIS_MARGIN_IN_CELSIUS - 0.1;

    hysteresisHeaterController_.setTargetTemperatureInCelsius(
        newTemperature
    );

    ASSERT_EQ(
        hysteresisHeaterController_.getTargetTemperatureInCelsius(),
        HEATER_PERSISTENT_CONFIG.targetTemperatureInCelsius
    );

    ASSERT_THAT(loggerSinkMock_.buffer, HasSubstr("ERROR"));
}

TEST_F(
    HysteresisHeaterControllerTest,
    GIVEN_hysteresisHeaterController_WHEN_isAtTargetTemperatureIsCalled_THEN_temperatureIsChecked
) {
    hysteresisHeaterController_.init(HEATER_PERSISTENT_CONFIG);

    constexpr float newTemperature = 60.5F;
    hysteresisHeaterController_.setTargetTemperatureInCelsius(
        newTemperature
    );

    ON_CALL(temperatureSensorMock_, getCelsius())
        .WillByDefault(Return(newTemperature));

    ASSERT_TRUE(hysteresisHeaterController_.isAtTargetTemperature());

    constexpr float tooBigTemperature =
        newTemperature + HYSTERESIS_MARGIN_IN_CELSIUS + 0.1;

    ON_CALL(temperatureSensorMock_, getCelsius())
        .WillByDefault(Return(tooBigTemperature));

    ASSERT_FALSE(hysteresisHeaterController_.isAtTargetTemperature());
}

TEST_F(
    HysteresisHeaterControllerTest,
    GIVEN_hysteresisHeaterController_WHEN_isAtTargetTemperatureIsCalled_THEN_hysteresisMarginIsTakenIntoAccount
) {
    hysteresisHeaterController_.init(HEATER_PERSISTENT_CONFIG);

    constexpr float slightlyHigherTemperature =
        HEATER_PERSISTENT_CONFIG.targetTemperatureInCelsius +
        (HYSTERESIS_MARGIN_IN_CELSIUS / 2);

    ON_CALL(temperatureSensorMock_, getCelsius())
        .WillByDefault(Return(slightlyHigherTemperature));

    ASSERT_TRUE(hysteresisHeaterController_.isAtTargetTemperature());

    constexpr float slightlyLowerTemperature =
        HEATER_PERSISTENT_CONFIG.targetTemperatureInCelsius -
        (HYSTERESIS_MARGIN_IN_CELSIUS / 2);

    ON_CALL(temperatureSensorMock_, getCelsius())
        .WillByDefault(Return(slightlyLowerTemperature));

    ASSERT_TRUE(hysteresisHeaterController_.isAtTargetTemperature());
}
}