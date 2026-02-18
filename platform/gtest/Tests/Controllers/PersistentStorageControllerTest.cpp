#include "application/System/Controllers/PersistentStorageController/PersistentStorageController.hpp"

#include "application/System/Config/ComponentConfig/DefaultPersistentConfig.hpp"
#include "application/System/Controllers/PersistentStorageController/PersistentData/AxisPersistentConfig.hpp"
#include "application/System/Controllers/PersistentStorageController/PersistentData/HeaterPersistentConfig.hpp"
#include "application/System/Controllers/PersistentStorageController/PersistentData/SpindlePersistentConfig.hpp"
#include "application/Utils/Byte.hpp"
#include "platform/gtest/Matchers/SpanMatcher.hpp"
#include "platform/gtest/Mocks/Controllers/LoggerSinkMock.hpp"
#include "platform/gtest/Mocks/Drivers/PersistentStorageMock.hpp"

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <algorithm>
#include <cctype>
#include <cstddef>
#include <cstdint>
#include <format>

using namespace testing;

namespace ATC {
MATCHER_P(ConfigBytesEqStruct, expected, "") { // NOLINT
    PersistentData comparedConfig = fromByteSpan<PersistentData>(arg);
    const PersistentData& expectedConfig = expected;

    return comparedConfig.xAxisConfig == expectedConfig.xAxisConfig &&
           comparedConfig.yAxisConfig == expectedConfig.yAxisConfig &&
           comparedConfig.zAxisConfig == expectedConfig.zAxisConfig &&
           comparedConfig.spindleConfig == expectedConfig.spindleConfig &&
           comparedConfig.heaterConfig == expectedConfig.heaterConfig &&
           comparedConfig.signature == expectedConfig.signature;
}

class PersistentStorageControllerTest : public Test {
public:
    static constexpr AxisPersistentConfig X_AXIS_PERSISTENT_CONFIG {
        .startPositionInMicrometers = 10,
        .endPositionInMicrometers = 1000,
        .speedInMillimetersPerSecond = 100
    };

    static constexpr AxisPersistentConfig Y_AXIS_PERSISTENT_CONFIG {
        .startPositionInMicrometers = 20,
        .endPositionInMicrometers = 2000,
        .speedInMillimetersPerSecond = 200
    };

    static constexpr AxisPersistentConfig Z_AXIS_PERSISTENT_CONFIG {
        .startPositionInMicrometers = 30,
        .endPositionInMicrometers = 3000,
        .speedInMillimetersPerSecond = 300
    };

    static constexpr SpindlePersistentConfig SPINDLE_PERSISTENT_CONFIG {
        .speedPercent = 20,
        .isDirectionClockwise = false,
        .timedRotationInMillis = 700
    };

    static constexpr HeaterPersistentConfig HEATER_PERSISTENT_CONFIG {
        .targetTemperatureInCelsius = 100
    };

    static constexpr PersistentData PERSISTENT_DATA {
        .xAxisConfig = X_AXIS_PERSISTENT_CONFIG,
        .yAxisConfig = Y_AXIS_PERSISTENT_CONFIG,
        .zAxisConfig = Z_AXIS_PERSISTENT_CONFIG,
        .spindleConfig = SPINDLE_PERSISTENT_CONFIG,
        .heaterConfig = HEATER_PERSISTENT_CONFIG,
        .signature = PersistentData::EXPECTED_SIGNATURE,
        .checksum = 10
    };

    static constexpr PersistentData DEFAULT_PERSISTENT_DATA {
        .xAxisConfig = DEFAULT_X_AXIS_CONFIG,
        .yAxisConfig = DEFAULT_Y_AXIS_CONFIG,
        .zAxisConfig = DEFAULT_Z_AXIS_CONFIG,
        .spindleConfig = DEFAULT_SPINDLE_CONFIG,
        .heaterConfig = DEFAULT_HEATER_CONFIG,
        .signature = PersistentData::EXPECTED_SIGNATURE,
        .checksum = 0
    };

    void expectConfigLoad(std::span<const uint8_t> configBytes) {
        EXPECT_CALL(persistentStorageMock_, read(_, _))
            .WillOnce([configBytes](uint32_t, std::span<uint8_t> buffer) {
                std::ranges::copy(configBytes, buffer.data());
            });
    }

    std::string getLowerCaseLoggerBuffer() const {
        std::string result = loggerSinkMock_.buffer;
        std::ranges::transform(result, result.begin(), tolower);

        return result;
    }

    LoggerSinkMock loggerSinkMock_ {};
    PersistentStorageMock persistentStorageMock_ {};

    PersistentStorageController persistentStorageController_ {
        loggerSinkMock_,
        persistentStorageMock_
    };
};

TEST_F(
    PersistentStorageControllerTest,
    GIVEN_persistentStorageController_WHEN_controllerIsInitialized_THEN_persistentStorageIsSetUp
) {
    EXPECT_CALL(persistentStorageMock_, init());
    persistentStorageController_.init();
}

TEST_F(
    PersistentStorageControllerTest,
    GIVEN_persistentStorageController_WHEN_differentSignatureIsDetected_THEN_defaultConfigIsSaved
) {
    PersistentData differentSignatureData = PERSISTENT_DATA;
    differentSignatureData.signature -= 1;

    const auto configBytes = toByteArray(differentSignatureData);
    expectConfigLoad(configBytes);

    EXPECT_CALL(
        persistentStorageMock_,
        write(0, ConfigBytesEqStruct(DEFAULT_PERSISTENT_DATA))
    );

    persistentStorageController_.init();
}

TEST_F(
    PersistentStorageControllerTest,
    GIVEN_persistentStorageController_WHEN_invalidSavedDataIsDetected_THEN_defaultConfigIsSaved
) {
    std::array<uint8_t, sizeof(PersistentData)> configBytes {};

    for (uint32_t i = 0; i < configBytes.size(); i++) {
        configBytes.at(i) = i % UINT8_MAX;
    }

    expectConfigLoad(configBytes);

    EXPECT_CALL(
        persistentStorageMock_,
        write(0, ConfigBytesEqStruct(DEFAULT_PERSISTENT_DATA))
    );

    persistentStorageController_.init();
}

TEST_F(
    PersistentStorageControllerTest,
    GIVEN_persistentStorageController_WHEN_validSavedDataIsDetected_THEN_noConfigIsSaved
) {
    PersistentData savedData {};

    EXPECT_CALL(persistentStorageMock_, write(0, _))
        .WillOnce([&](uint32_t, std::span<uint8_t> buffer) mutable {
            savedData = fromByteSpan<PersistentData>(buffer);
        });

    persistentStorageController_.init();

    const auto savedDataBytes = toByteArray(savedData);
    expectConfigLoad(savedDataBytes);

    EXPECT_CALL(
        persistentStorageMock_,
        write(0, ConfigBytesEqStruct(DEFAULT_PERSISTENT_DATA))
    )
        .Times(0);

    persistentStorageController_.init();
}

TEST_F(
    PersistentStorageControllerTest,
    GIVEN_persistentStorageController_WHEN_controllerIsInitialized_THEN_xAxisConfigIsLogged
) {
    const auto configBytes = toByteArray(PERSISTENT_DATA);
    expectConfigLoad(configBytes);

    persistentStorageController_.init();

    const std::string lowerCaseLog = getLowerCaseLoggerBuffer();

    ASSERT_THAT(
        lowerCaseLog,
        HasSubstr(
            std::format(
                "start position [μm]: {}",
                X_AXIS_PERSISTENT_CONFIG.startPositionInMicrometers
            )
        )
    );

    ASSERT_THAT(
        lowerCaseLog,
        HasSubstr(
            std::format(
                "end position [μm]: {}",
                X_AXIS_PERSISTENT_CONFIG.endPositionInMicrometers
            )
        )
    );

    ASSERT_THAT(
        lowerCaseLog,
        HasSubstr(
            std::format(
                "speed [mm/s]: {}",
                X_AXIS_PERSISTENT_CONFIG.speedInMillimetersPerSecond
            )
        )
    );
}

TEST_F(
    PersistentStorageControllerTest,
    GIVEN_persistentStorageController_WHEN_controllerIsInitialized_THEN_yAxisConfigIsLogged
) {
    const auto configBytes = toByteArray(PERSISTENT_DATA);
    expectConfigLoad(configBytes);

    persistentStorageController_.init();

    const std::string lowerCaseLog = getLowerCaseLoggerBuffer();

    ASSERT_THAT(
        lowerCaseLog,
        HasSubstr(
            std::format(
                "start position [μm]: {}",
                Y_AXIS_PERSISTENT_CONFIG.startPositionInMicrometers
            )
        )
    );

    ASSERT_THAT(
        lowerCaseLog,
        HasSubstr(
            std::format(
                "end position [μm]: {}",
                Y_AXIS_PERSISTENT_CONFIG.endPositionInMicrometers
            )
        )
    );

    ASSERT_THAT(
        lowerCaseLog,
        HasSubstr(
            std::format(
                "speed [mm/s]: {}",
                Y_AXIS_PERSISTENT_CONFIG.speedInMillimetersPerSecond
            )
        )
    );
}

TEST_F(
    PersistentStorageControllerTest,
    GIVEN_persistentStorageController_WHEN_controllerIsInitialized_THEN_zAxisConfigIsLogged
) {
    const auto configBytes = toByteArray(PERSISTENT_DATA);
    expectConfigLoad(configBytes);

    persistentStorageController_.init();

    const std::string lowerCaseLog = getLowerCaseLoggerBuffer();

    ASSERT_THAT(
        lowerCaseLog,
        HasSubstr(
            std::format(
                "start position [μm]: {}",
                Z_AXIS_PERSISTENT_CONFIG.startPositionInMicrometers
            )
        )
    );

    ASSERT_THAT(
        lowerCaseLog,
        HasSubstr(
            std::format(
                "end position [μm]: {}",
                Z_AXIS_PERSISTENT_CONFIG.endPositionInMicrometers
            )
        )
    );

    ASSERT_THAT(
        lowerCaseLog,
        HasSubstr(
            std::format(
                "speed [mm/s]: {}",
                Z_AXIS_PERSISTENT_CONFIG.speedInMillimetersPerSecond
            )
        )
    );
}

TEST_F(
    PersistentStorageControllerTest,
    GIVEN_persistentStorageController_WHEN_controllerIsInitialized_THEN_spindleConfigIsLogged
) {
    const auto configBytes = toByteArray(PERSISTENT_DATA);
    expectConfigLoad(configBytes);

    persistentStorageController_.init();

    const std::string lowerCaseLog = getLowerCaseLoggerBuffer();

    ASSERT_THAT(
        lowerCaseLog,
        HasSubstr(
            std::format(
                "speed [%]: {}", SPINDLE_PERSISTENT_CONFIG.speedPercent
            )
        )
    );

    ASSERT_THAT(
        lowerCaseLog,
        HasSubstr(
            std::format(
                "clockwise: {}",
                SPINDLE_PERSISTENT_CONFIG.isDirectionClockwise
            )
        )
    );

    ASSERT_THAT(
        lowerCaseLog,
        HasSubstr(
            std::format(
                "rotation [ms]: {}",
                SPINDLE_PERSISTENT_CONFIG.timedRotationInMillis
            )
        )
    );
}

TEST_F(
    PersistentStorageControllerTest,
    GIVEN_persistentStorageController_WHEN_controllerIsInitialized_THEN_heaterConfigIsLogged
) {
    const auto configBytes = toByteArray(PERSISTENT_DATA);
    expectConfigLoad(configBytes);

    persistentStorageController_.init();

    const std::string lowerCaseLog = getLowerCaseLoggerBuffer();

    ASSERT_THAT(
        lowerCaseLog,
        HasSubstr(
            std::format(
                "temperature [°c]: {}",
                HEATER_PERSISTENT_CONFIG.targetTemperatureInCelsius
            )
        )
    );
}

TEST_F(
    PersistentStorageControllerTest,
    GIVEN_persistentStorageController_WHEN_saveXAxisConfigIsCalled_THEN_statusIsLogged
) {
    constexpr AxisPersistentConfig newConfig {
        .startPositionInMicrometers =
            X_AXIS_PERSISTENT_CONFIG.startPositionInMicrometers + 10,
        .endPositionInMicrometers =
            X_AXIS_PERSISTENT_CONFIG.endPositionInMicrometers + 1000,
        .speedInMillimetersPerSecond =
            X_AXIS_PERSISTENT_CONFIG.speedInMillimetersPerSecond + 100
    };

    persistentStorageController_.saveXAxisConfig(newConfig);

    ASSERT_THAT(getLowerCaseLoggerBuffer(), HasSubstr("saved x"));
}

TEST_F(
    PersistentStorageControllerTest,
    GIVEN_persistentStorageController_WHEN_saveXAxisConfigIsCalled_THEN_onlyNewConfigIsSaved
) {
    constexpr AxisPersistentConfig newConfig {
        .startPositionInMicrometers =
            X_AXIS_PERSISTENT_CONFIG.startPositionInMicrometers + 10,
        .endPositionInMicrometers =
            X_AXIS_PERSISTENT_CONFIG.endPositionInMicrometers + 1000,
        .speedInMillimetersPerSecond =
            X_AXIS_PERSISTENT_CONFIG.speedInMillimetersPerSecond + 100
    };

    const auto newConfigBytes = toByteArray(newConfig);
    const uint32_t configAddress = offsetof(PersistentData, xAxisConfig);
    const uint32_t checksumAddress = offsetof(PersistentData, checksum);

    {
        InSequence sequence;

        EXPECT_CALL(
            persistentStorageMock_,
            write(configAddress, SpanValueEq(newConfigBytes))
        )
            .Times(1)
            .RetiresOnSaturation();

        EXPECT_CALL(persistentStorageMock_, write(checksumAddress, _))
            .Times(1);

        persistentStorageController_.saveXAxisConfig(newConfig);
    }

    EXPECT_CALL(persistentStorageMock_, write(configAddress, _)).Times(0);
    persistentStorageController_.saveXAxisConfig(newConfig);
}

TEST_F(
    PersistentStorageControllerTest,
    GIVEN_persistentStorageController_WHEN_saveYAxisConfigIsCalled_THEN_statusIsLogged
) {
    constexpr AxisPersistentConfig newConfig {
        .startPositionInMicrometers =
            Y_AXIS_PERSISTENT_CONFIG.startPositionInMicrometers + 10,
        .endPositionInMicrometers =
            Y_AXIS_PERSISTENT_CONFIG.endPositionInMicrometers + 1000,
        .speedInMillimetersPerSecond =
            Y_AXIS_PERSISTENT_CONFIG.speedInMillimetersPerSecond + 100
    };

    persistentStorageController_.saveYAxisConfig(newConfig);

    std::ranges::transform(
        loggerSinkMock_.buffer, loggerSinkMock_.buffer.begin(), tolower
    );

    ASSERT_THAT(loggerSinkMock_.buffer, HasSubstr("saved y"));
}

TEST_F(
    PersistentStorageControllerTest,
    GIVEN_persistentStorageController_WHEN_saveYAxisConfigIsCalled_THEN_onlyNewConfigIsSaved
) {
    constexpr AxisPersistentConfig newConfig {
        .startPositionInMicrometers =
            Y_AXIS_PERSISTENT_CONFIG.startPositionInMicrometers + 10,
        .endPositionInMicrometers =
            Y_AXIS_PERSISTENT_CONFIG.endPositionInMicrometers + 1000,
        .speedInMillimetersPerSecond =
            Y_AXIS_PERSISTENT_CONFIG.speedInMillimetersPerSecond + 100
    };

    const auto newConfigBytes = toByteArray(newConfig);
    const uint32_t configAddress = offsetof(PersistentData, yAxisConfig);
    const uint32_t checksumAddress = offsetof(PersistentData, checksum);

    {
        InSequence sequence;

        EXPECT_CALL(
            persistentStorageMock_,
            write(configAddress, SpanValueEq(newConfigBytes))
        )
            .Times(1)
            .RetiresOnSaturation();

        EXPECT_CALL(persistentStorageMock_, write(checksumAddress, _))
            .Times(1);

        persistentStorageController_.saveYAxisConfig(newConfig);
    }

    EXPECT_CALL(persistentStorageMock_, write(configAddress, _)).Times(0);
    persistentStorageController_.saveYAxisConfig(newConfig);
}

TEST_F(
    PersistentStorageControllerTest,
    GIVEN_persistentStorageController_WHEN_saveZAxisConfigIsCalled_THEN_statusIsLogged
) {
    constexpr AxisPersistentConfig newConfig {
        .startPositionInMicrometers =
            Z_AXIS_PERSISTENT_CONFIG.startPositionInMicrometers + 10,
        .endPositionInMicrometers =
            Z_AXIS_PERSISTENT_CONFIG.endPositionInMicrometers + 1000,
        .speedInMillimetersPerSecond =
            Z_AXIS_PERSISTENT_CONFIG.speedInMillimetersPerSecond + 100
    };

    persistentStorageController_.saveZAxisConfig(newConfig);

    std::ranges::transform(
        loggerSinkMock_.buffer, loggerSinkMock_.buffer.begin(), tolower
    );

    ASSERT_THAT(loggerSinkMock_.buffer, HasSubstr("saved z"));
}

TEST_F(
    PersistentStorageControllerTest,
    GIVEN_persistentStorageController_WHEN_saveZAxisConfigIsCalled_THEN_onlyNewConfigIsSaved
) {
    constexpr AxisPersistentConfig newConfig {
        .startPositionInMicrometers =
            Z_AXIS_PERSISTENT_CONFIG.startPositionInMicrometers + 10,
        .endPositionInMicrometers =
            Z_AXIS_PERSISTENT_CONFIG.endPositionInMicrometers + 1000,
        .speedInMillimetersPerSecond =
            Z_AXIS_PERSISTENT_CONFIG.speedInMillimetersPerSecond + 100
    };

    const auto newConfigBytes = toByteArray(newConfig);
    const uint32_t configAddress = offsetof(PersistentData, zAxisConfig);
    const uint32_t checksumAddress = offsetof(PersistentData, checksum);

    {
        InSequence sequence;

        EXPECT_CALL(
            persistentStorageMock_,
            write(configAddress, SpanValueEq(newConfigBytes))
        )
            .Times(1)
            .RetiresOnSaturation();

        EXPECT_CALL(persistentStorageMock_, write(checksumAddress, _))
            .Times(1);

        persistentStorageController_.saveZAxisConfig(newConfig);
    }

    EXPECT_CALL(persistentStorageMock_, write(configAddress, _)).Times(0);
    persistentStorageController_.saveZAxisConfig(newConfig);
}

TEST_F(
    PersistentStorageControllerTest,
    GIVEN_persistentStorageController_WHEN_saveSpindleConfigIsCalled_THEN_statusIsLogged
) {
    constexpr SpindlePersistentConfig newConfig {
        .speedPercent = SPINDLE_PERSISTENT_CONFIG.speedPercent + 10,
        .isDirectionClockwise =
            !SPINDLE_PERSISTENT_CONFIG.isDirectionClockwise,
        .timedRotationInMillis =
            SPINDLE_PERSISTENT_CONFIG.timedRotationInMillis + 100
    };

    persistentStorageController_.saveSpindleConfig(newConfig);

    std::ranges::transform(
        loggerSinkMock_.buffer, loggerSinkMock_.buffer.begin(), tolower
    );

    ASSERT_THAT(loggerSinkMock_.buffer, HasSubstr("saved spindle"));
}

TEST_F(
    PersistentStorageControllerTest,
    GIVEN_persistentStorageController_WHEN_saveSpindleConfigIsCalled_THEN_onlyNewConfigIsSaved
) {
    constexpr SpindlePersistentConfig newConfig {
        .speedPercent = SPINDLE_PERSISTENT_CONFIG.speedPercent + 10,
        .isDirectionClockwise =
            !SPINDLE_PERSISTENT_CONFIG.isDirectionClockwise,
        .timedRotationInMillis =
            SPINDLE_PERSISTENT_CONFIG.timedRotationInMillis + 100
    };

    const auto newConfigBytes = toByteArray(newConfig);
    const uint32_t configAddress =
        offsetof(PersistentData, spindleConfig);
    const uint32_t checksumAddress = offsetof(PersistentData, checksum);

    {
        InSequence sequence;

        EXPECT_CALL(
            persistentStorageMock_,
            write(configAddress, SpanValueEq(newConfigBytes))
        )
            .Times(1)
            .RetiresOnSaturation();

        EXPECT_CALL(persistentStorageMock_, write(checksumAddress, _))
            .Times(1);

        persistentStorageController_.saveSpindleConfig(newConfig);
    }

    EXPECT_CALL(persistentStorageMock_, write(configAddress, _)).Times(0);
    persistentStorageController_.saveSpindleConfig(newConfig);
}

TEST_F(
    PersistentStorageControllerTest,
    GIVEN_persistentStorageController_WHEN_saveHeaterConfigIsCalled_THEN_statusIsLogged
) {
    constexpr HeaterPersistentConfig newConfig {
        .targetTemperatureInCelsius =
            HEATER_PERSISTENT_CONFIG.targetTemperatureInCelsius + 10
    };

    persistentStorageController_.saveHeaterConfig(newConfig);

    std::ranges::transform(
        loggerSinkMock_.buffer, loggerSinkMock_.buffer.begin(), tolower
    );

    ASSERT_THAT(loggerSinkMock_.buffer, HasSubstr("saved heater"));
}

TEST_F(
    PersistentStorageControllerTest,
    GIVEN_persistentStorageController_WHEN_saveHeaterConfigIsCalled_THEN_onlyNewConfigIsSaved
) {
    constexpr HeaterPersistentConfig newConfig {
        .targetTemperatureInCelsius =
            HEATER_PERSISTENT_CONFIG.targetTemperatureInCelsius + 10
    };

    const auto newConfigBytes = toByteArray(newConfig);
    const uint32_t configAddress = offsetof(PersistentData, heaterConfig);
    const uint32_t checksumAddress = offsetof(PersistentData, checksum);

    {
        InSequence sequence;

        EXPECT_CALL(
            persistentStorageMock_,
            write(configAddress, SpanValueEq(newConfigBytes))
        )
            .Times(1)
            .RetiresOnSaturation();

        EXPECT_CALL(persistentStorageMock_, write(checksumAddress, _))
            .Times(1);

        persistentStorageController_.saveHeaterConfig(newConfig);
    }

    EXPECT_CALL(persistentStorageMock_, write(configAddress, _)).Times(0);
    persistentStorageController_.saveHeaterConfig(newConfig);
}

TEST_F(
    PersistentStorageControllerTest,
    GIVEN_persistentStorageController_WHEN_loadXAxisConfigIsCalled_THEN_persistentConfigIsLoaded
) {
    const auto configBytes = toByteArray(X_AXIS_PERSISTENT_CONFIG);

    expectConfigLoad(configBytes);

    const AxisPersistentConfig loadedConfig =
        persistentStorageController_.loadXAxisConfig();
    const auto loadedBytes = toByteArray(loadedConfig);

    ASSERT_THAT(loadedBytes, SpanValueEq(configBytes));
}

TEST_F(
    PersistentStorageControllerTest,
    GIVEN_persistentStorageController_WHEN_loadYAxisConfigIsCalled_THEN_persistentConfigIsLoaded
) {
    const auto configBytes = toByteArray(Y_AXIS_PERSISTENT_CONFIG);

    expectConfigLoad(configBytes);

    const AxisPersistentConfig loadedConfig =
        persistentStorageController_.loadYAxisConfig();
    const auto loadedBytes = toByteArray(loadedConfig);

    ASSERT_THAT(loadedBytes, SpanValueEq(configBytes));
}

TEST_F(
    PersistentStorageControllerTest,
    GIVEN_persistentStorageController_WHEN_loadZAxisConfigIsCalled_THEN_persistentConfigIsLoaded
) {
    const auto configBytes = toByteArray(Z_AXIS_PERSISTENT_CONFIG);

    expectConfigLoad(configBytes);

    const AxisPersistentConfig loadedConfig =
        persistentStorageController_.loadZAxisConfig();
    const auto loadedBytes = toByteArray(loadedConfig);

    ASSERT_THAT(loadedBytes, SpanValueEq(configBytes));
}

TEST_F(
    PersistentStorageControllerTest,
    GIVEN_persistentStorageController_WHEN_loadSpindleConfigIsCalled_THEN_persistentConfigIsLoaded
) {
    const auto configBytes = toByteArray(SPINDLE_PERSISTENT_CONFIG);

    expectConfigLoad(configBytes);

    const SpindlePersistentConfig loadedConfig =
        persistentStorageController_.loadSpindleConfig();
    const auto loadedBytes = toByteArray(loadedConfig);

    ASSERT_THAT(loadedBytes, SpanValueEq(configBytes));
}

TEST_F(
    PersistentStorageControllerTest,
    GIVEN_persistentStorageController_WHEN_loadHeaterConfigIsCalled_THEN_persistentConfigIsLoaded
) {
    const auto configBytes = toByteArray(HEATER_PERSISTENT_CONFIG);

    expectConfigLoad(configBytes);

    const HeaterPersistentConfig loadedConfig =
        persistentStorageController_.loadHeaterConfig();
    const auto loadedBytes = toByteArray(loadedConfig);

    ASSERT_THAT(loadedBytes, SpanValueEq(configBytes));
}
}