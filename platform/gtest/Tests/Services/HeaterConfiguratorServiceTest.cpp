#include "application/System/Services/HeaterConfiguratorService/HeaterConfiguratorService.hpp"

#include "application/System/Controllers/PersistentStorageController/PersistentData/HeaterPersistentConfig.hpp"
#include "platform/gtest/Mocks/Controllers/HeaterControllerMock.hpp"
#include "platform/gtest/Mocks/Controllers/PersistentStorageControllerMock.hpp"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

using namespace testing;

namespace ATC {
class HeaterConfiguratorServiceTest : public Test {
public:
    static constexpr HeaterConfiguratorParameters PARAMETERS {
        .temperatureStepInCelsius = 1,
        .minTemperatureInCelsius = 60,
        .maxTemperatureInCelsius = 300,
    };

    static constexpr bool IS_ON = false;
    static constexpr float TARGET_TEMPERATURE =
        PARAMETERS.maxTemperatureInCelsius - 11.0F;

    PersistentStorageControllerMock persistentStorageControllerMock_ {};
    HeaterControllerMock heaterControllerMock_ {};

    HeaterConfiguratorService heaterConfiguratorService_ {
        persistentStorageControllerMock_,
        heaterControllerMock_,
        PARAMETERS
    };

    void setBufferedConfig() {
        EXPECT_CALL(heaterControllerMock_, isOn())
            .WillOnce(Return(IS_ON));

        EXPECT_CALL(
            heaterControllerMock_, getTargetTemperatureInCelsius()
        )
            .WillOnce(Return(TARGET_TEMPERATURE));

        heaterConfiguratorService_.resetBufferedConfig();
    }
};

TEST_F(
    HeaterConfiguratorServiceTest,
    GIVEN_heaterConfiguratorService_WHEN_resetBufferedConfigIsCalled_THEN_configsAreReadFromController
) {
    setBufferedConfig();

    ASSERT_EQ(heaterConfiguratorService_.isOn(), IS_ON);
    ASSERT_EQ(
        heaterConfiguratorService_.getTemperatureInCelsius(),
        TARGET_TEMPERATURE
    );
}

TEST_F(
    HeaterConfiguratorServiceTest,
    GIVEN_heaterConfiguratorService_WHEN_increaseTemperatureIsCalled_THEN_temperatureDoesNotExceedMaxValue
) {
    setBufferedConfig();

    constexpr uint32_t increments =
        uint32_t(
            (PARAMETERS.maxTemperatureInCelsius - TARGET_TEMPERATURE) /
            PARAMETERS.temperatureStepInCelsius
        ) +
        10;

    for (uint32_t i = 0; i < increments; i++) {
        heaterConfiguratorService_.increaseTemperatureInCelsius();
    }

    ASSERT_EQ(
        heaterConfiguratorService_.getTemperatureInCelsius(),
        PARAMETERS.maxTemperatureInCelsius
    );
}

TEST_F(
    HeaterConfiguratorServiceTest,
    GIVEN_heaterConfiguratorService_WHEN_decreaseTemperatureIsCalled_THEN_temperatureDoesNotExceedMinValue
) {
    setBufferedConfig();

    constexpr uint32_t decrements =
        uint32_t(
            (TARGET_TEMPERATURE - PARAMETERS.minTemperatureInCelsius) /
            PARAMETERS.temperatureStepInCelsius
        ) +
        10;

    for (uint32_t i = 0; i < decrements; i++) {
        heaterConfiguratorService_.decreaseTemperatureInCelsius();
    }

    ASSERT_EQ(
        heaterConfiguratorService_.getTemperatureInCelsius(),
        PARAMETERS.minTemperatureInCelsius
    );
}

TEST_F(
    HeaterConfiguratorServiceTest,
    GIVEN_heaterConfiguratorService_WHEN_saveTemperatureIsCalled_THEN_controllerTemperatureIsUpdated
) {
    setBufferedConfig();

    heaterConfiguratorService_.increaseTemperatureInCelsius();

    EXPECT_CALL(
        heaterControllerMock_,
        setTargetTemperatureInCelsius(
            TARGET_TEMPERATURE + PARAMETERS.temperatureStepInCelsius
        )
    );

    heaterConfiguratorService_.saveTemperatureInCelsius();
}

TEST_F(
    HeaterConfiguratorServiceTest,
    GIVEN_heaterConfiguratorService_WHEN_saveTemperatureIsCalled_THEN_persistentConfigIsSaved
) {
    setBufferedConfig();

    heaterConfiguratorService_.increaseTemperatureInCelsius();

    EXPECT_CALL(
        persistentStorageControllerMock_,
        saveHeaterConfig(
            HeaterPersistentConfig {
                TARGET_TEMPERATURE + PARAMETERS.temperatureStepInCelsius
            }
        )
    );

    heaterConfiguratorService_.saveTemperatureInCelsius();
}

TEST_F(
    HeaterConfiguratorServiceTest,
    GIVEN_heaterConfiguratorService_WHEN_turnOnIsCalled_THEN_heaterStateIsUpdated
) {
    heaterConfiguratorService_.turnOn();

    ASSERT_TRUE(heaterConfiguratorService_.isOn());
}

TEST_F(
    HeaterConfiguratorServiceTest,
    GIVEN_heaterConfiguratorService_WHEN_turnOffIsCalled_THEN_heaterStateIsUpdated
) {
    heaterConfiguratorService_.turnOff();

    ASSERT_FALSE(heaterConfiguratorService_.isOn());
}

TEST_F(
    HeaterConfiguratorServiceTest,
    GIVEN_heaterConfiguratorService_WHEN_saveHeaterStateIsCalled_THEN_controllerIsToggled
) {
    heaterConfiguratorService_.turnOff();
    EXPECT_CALL(heaterControllerMock_, turnOff());
    heaterConfiguratorService_.saveHeaterState();

    heaterConfiguratorService_.turnOn();
    EXPECT_CALL(heaterControllerMock_, turnOn());
    heaterConfiguratorService_.saveHeaterState();
}

TEST_F(
    HeaterConfiguratorServiceTest,
    GIVEN_heaterConfiguratorService_WHEN_getStoredConfigIsCalled_THEN_controllerConfigIsReturned
) {
    EXPECT_CALL(heaterControllerMock_, getTargetTemperatureInCelsius())
        .WillOnce(Return(TARGET_TEMPERATURE));

    const HeaterPersistentConfig config =
        heaterConfiguratorService_.getStoredConfig();

    ASSERT_EQ(config.targetTemperatureInCelsius, TARGET_TEMPERATURE);
}

}