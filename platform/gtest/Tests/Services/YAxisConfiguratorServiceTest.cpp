#include "application/System/Services/AxisConfiguratorService/YAxisConfiguratorService/YAxisConfiguratorService.hpp"

#include "application/System/Controllers/PersistentStorageController/PersistentData/AxisPersistentConfig.hpp"
#include "platform/gtest/Mocks/Controllers/AxisControllerMock.hpp"
#include "platform/gtest/Mocks/Controllers/PersistentStorageControllerMock.hpp"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

using namespace testing;

namespace ATC {
class YAxisConfiguratorServiceTest : public Test {
public:
    static constexpr AxisConfiguratorParameters PARAMETERS {
        .positionStepInMicrometers = 5,
        .speedStepInMillimetersPerSecond = 1,
        .speedShowcasePositionInMicrometers = 200,
        .minPositionInMicrometers = 10,
        .maxPositionInMicrometers = 1000,
        .minSpeedInMillimetersPerSecond = 3,
        .maxSpeedInMillimetersPerSecond = 300,
    };

    PersistentStorageControllerMock persistentStorageControllerMock_ {};
    AxisControllerMock axisControllerMock_ {};

    YAxisConfiguratorService yAxisConfiguratorService_ {
        persistentStorageControllerMock_,
        axisControllerMock_,
        PARAMETERS
    };
};

TEST_F(
    YAxisConfiguratorServiceTest,
    GIVEN_yAxisConfiguratorService_WHEN_saveStartPositionIsCalled_THEN_persistentConfigIsSaved
) {
    constexpr AxisPersistentConfig config {
        .startPositionInMicrometers =
            PARAMETERS.minPositionInMicrometers + 10,
        .endPositionInMicrometers =
            PARAMETERS.maxPositionInMicrometers - 10,
        .speedInMillimetersPerSecond =
            PARAMETERS.maxSpeedInMillimetersPerSecond - 10
    };

    EXPECT_CALL(axisControllerMock_, getStartPositionInMicrometers())
        .WillOnce(Return(config.startPositionInMicrometers));
    EXPECT_CALL(axisControllerMock_, getEndPositionInMicrometers())
        .WillOnce(Return(config.endPositionInMicrometers));
    EXPECT_CALL(axisControllerMock_, getSpeedInMillimetersPerSecond())
        .WillOnce(Return(config.speedInMillimetersPerSecond));

    yAxisConfiguratorService_.resetBufferedConfig();

    EXPECT_CALL(
        persistentStorageControllerMock_, saveYAxisConfig(config)
    );

    yAxisConfiguratorService_.saveStartPosition();
}
}