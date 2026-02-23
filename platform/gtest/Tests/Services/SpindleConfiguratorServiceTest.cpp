#include "application/System/Services/SpindleConfiguratorService/SpindleConfiguratorService.hpp"

#include "application/System/Controllers/PersistentStorageController/PersistentData/SpindlePersistentConfig.hpp"
#include "application/System/Services/SpindleConfiguratorService/SpindleConfiguratorParameters.hpp"
#include "platform/gtest/Mocks/Controllers/PersistentStorageControllerMock.hpp"
#include "platform/gtest/Mocks/Controllers/SpindleControllerMock.hpp"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

using namespace testing;

namespace ATC {
class SpindleConfiguratorServiceTest : public Test {
public:
    static constexpr SpindleConfiguratorParameters PARAMETERS {
        .showcaseRotationTimeInMillis = 600,
        .speedPercentStep = 1,
        .rotationTimeStepInMillis = 5,
    };

    static constexpr uint8_t SPEED_PERCENT = 85;
    static constexpr bool IS_DIRECTION_CLOCKWISE = true;
    static constexpr uint32_t ROTATION_TIME = 3000;

    PersistentStorageControllerMock persistentStorageControllerMock_ {};
    SpindleControllerMock spindleControllerMock_ {};

    SpindleConfiguratorService spindleConfiguratorService_ {
        persistentStorageControllerMock_,
        spindleControllerMock_,
        PARAMETERS
    };

    void setBufferedConfig() {
        EXPECT_CALL(spindleControllerMock_, getSpeedPercent())
            .WillOnce(Return(SPEED_PERCENT));

        EXPECT_CALL(spindleControllerMock_, isDirectionClockwise())
            .WillOnce(Return(IS_DIRECTION_CLOCKWISE));

        EXPECT_CALL(spindleControllerMock_, getRotationTimeInMillis())
            .WillOnce(Return(ROTATION_TIME));

        spindleConfiguratorService_.resetBufferedConfig();
    }
};

TEST_F(
    SpindleConfiguratorServiceTest,
    GIVEN_spindleConfiguratorService_WHEN_resetBufferedConfigIsCalled_THEN_configsAreReadFromController
) {
    setBufferedConfig();

    ASSERT_EQ(
        spindleConfiguratorService_.getSpeedPercent(), SPEED_PERCENT
    );
    ASSERT_EQ(
        spindleConfiguratorService_.isDirectionClockwise(),
        IS_DIRECTION_CLOCKWISE
    );
    ASSERT_EQ(
        spindleConfiguratorService_.getRotationTimeInMillis(),
        ROTATION_TIME
    );
}

TEST_F(
    SpindleConfiguratorServiceTest,
    GIVEN_spindleConfiguratorService_WHEN_showcaseRotationIsCalled_THEN_controllerStartsTimedRotation
) {
    setBufferedConfig();

    EXPECT_CALL(
        spindleControllerMock_,
        startTimedRotation(PARAMETERS.showcaseRotationTimeInMillis)
    );

    spindleConfiguratorService_.showcaseRotation();
}

TEST_F(
    SpindleConfiguratorServiceTest,
    GIVEN_spindleConfiguratorService_WHEN_increaseSpeedPercentIsCalled_THEN_speedPercentIncreases
) {
    setBufferedConfig();

    spindleConfiguratorService_.increaseSpeedPercent();

    ASSERT_EQ(
        spindleConfiguratorService_.getSpeedPercent(),
        SPEED_PERCENT + PARAMETERS.speedPercentStep
    );
}

TEST_F(
    SpindleConfiguratorServiceTest,
    GIVEN_spindleConfiguratorService_WHEN_decreaseSpeedPercentIsCalled_THEN_speedPercentDecreases
) {
    setBufferedConfig();

    spindleConfiguratorService_.decreaseSpeedPercent();

    ASSERT_EQ(
        spindleConfiguratorService_.getSpeedPercent(),
        SPEED_PERCENT - PARAMETERS.speedPercentStep
    );
}

TEST_F(
    SpindleConfiguratorServiceTest,
    GIVEN_spindleConfiguratorService_WHEN_saveSpeedPercentIsCalled_THEN_controllerSpeedIsUpdated
) {
    setBufferedConfig();

    spindleConfiguratorService_.increaseSpeedPercent();

    EXPECT_CALL(
        spindleControllerMock_,
        setSpeedPercent(SPEED_PERCENT + PARAMETERS.speedPercentStep)
    );

    spindleConfiguratorService_.saveSpeedPercent();
}

TEST_F(
    SpindleConfiguratorServiceTest,
    GIVEN_spindleConfiguratorService_WHEN_saveSpeedPercentIsCalled_THEN_persistentConfigIsSaved
) {
    setBufferedConfig();

    constexpr SpindlePersistentConfig config {
        .speedPercent = SPEED_PERCENT,
        .isDirectionClockwise = IS_DIRECTION_CLOCKWISE,
        .timedRotationInMillis = ROTATION_TIME
    };

    EXPECT_CALL(
        persistentStorageControllerMock_, saveSpindleConfig(config)
    );

    spindleConfiguratorService_.saveSpeedPercent();
}

TEST_F(
    SpindleConfiguratorServiceTest,
    GIVEN_spindleConfiguratorService_WHEN_setDirectionClockwiseIsCalled_THEN_directionIsSet
) {
    setBufferedConfig();

    spindleConfiguratorService_.setDirectionClockwise();
    ASSERT_TRUE(spindleConfiguratorService_.isDirectionClockwise());

    spindleConfiguratorService_.setDirectionCounterClockwise();
    ASSERT_FALSE(spindleConfiguratorService_.isDirectionClockwise());
}

TEST_F(
    SpindleConfiguratorServiceTest,
    GIVEN_spindleConfiguratorService_WHEN_saveDirectonIsCalled_THEN_controllerDirectionIsUpdated
) {
    setBufferedConfig();

    spindleConfiguratorService_.setDirectionClockwise();
    EXPECT_CALL(spindleControllerMock_, setDirectionClockwise());
    spindleConfiguratorService_.saveDirection();

    spindleConfiguratorService_.setDirectionCounterClockwise();
    EXPECT_CALL(spindleControllerMock_, setDirectionCounterClockwise());
    spindleConfiguratorService_.saveDirection();
}

TEST_F(
    SpindleConfiguratorServiceTest,
    GIVEN_spindleConfiguratorService_WHEN_saveDirectionIsCalled_THEN_persistentConfigIsSaved
) {
    setBufferedConfig();

    constexpr SpindlePersistentConfig config {
        .speedPercent = SPEED_PERCENT,
        .isDirectionClockwise = IS_DIRECTION_CLOCKWISE,
        .timedRotationInMillis = ROTATION_TIME
    };

    EXPECT_CALL(
        persistentStorageControllerMock_, saveSpindleConfig(config)
    );

    spindleConfiguratorService_.saveDirection();
}

TEST_F(
    SpindleConfiguratorServiceTest,
    GIVEN_spindleConfiguratorService_WHEN_increaseRotationTimeIsCalled_THEN_rotationTimeIncreases
) {
    setBufferedConfig();

    spindleConfiguratorService_.increaseRotationTimeInMillis();

    ASSERT_EQ(
        spindleConfiguratorService_.getRotationTimeInMillis(),
        ROTATION_TIME + PARAMETERS.rotationTimeStepInMillis
    );
}

TEST_F(
    SpindleConfiguratorServiceTest,
    GIVEN_spindleConfiguratorService_WHEN_decreaseRotationTimeIsCalled_THEN_rotationTimeDecreases
) {
    setBufferedConfig();

    spindleConfiguratorService_.decreaseRotationTimeInMillis();

    ASSERT_EQ(
        spindleConfiguratorService_.getRotationTimeInMillis(),
        ROTATION_TIME - PARAMETERS.rotationTimeStepInMillis
    );
}

TEST_F(
    SpindleConfiguratorServiceTest,
    GIVEN_spindleConfiguratorService_WHEN_saveRotationTimeIsCalled_THEN_controllerRotationTimeIsUpdated
) {
    setBufferedConfig();

    spindleConfiguratorService_.increaseRotationTimeInMillis();

    EXPECT_CALL(
        spindleControllerMock_,
        setRotationTimeInMillis(
            ROTATION_TIME + PARAMETERS.rotationTimeStepInMillis
        )
    );

    spindleConfiguratorService_.saveRotationTimeInMillis();
}

TEST_F(
    SpindleConfiguratorServiceTest,
    GIVEN_spindleConfiguratorService_WHEN_saveRotationTimeIsCalled_THEN_persistentConfigIsSaved
) {
    setBufferedConfig();

    constexpr SpindlePersistentConfig config {
        .speedPercent = SPEED_PERCENT,
        .isDirectionClockwise = IS_DIRECTION_CLOCKWISE,
        .timedRotationInMillis = ROTATION_TIME
    };

    EXPECT_CALL(
        persistentStorageControllerMock_, saveSpindleConfig(config)
    );

    spindleConfiguratorService_.saveRotationTimeInMillis();
}

TEST_F(
    SpindleConfiguratorServiceTest,
    GIVEN_spindleConfiguratorService_WHEN_getStoredConfigIsCalled_THEN_controllerConfigIsReturned
) {
    EXPECT_CALL(spindleControllerMock_, getSpeedPercent())
        .WillOnce(Return(SPEED_PERCENT));

    EXPECT_CALL(spindleControllerMock_, isDirectionClockwise())
        .WillOnce(Return(IS_DIRECTION_CLOCKWISE));

    EXPECT_CALL(spindleControllerMock_, getRotationTimeInMillis())
        .WillOnce(Return(ROTATION_TIME));

    const SpindlePersistentConfig config =
        spindleConfiguratorService_.getStoredConfig();

    ASSERT_EQ(config.speedPercent, SPEED_PERCENT);
    ASSERT_EQ(config.isDirectionClockwise, IS_DIRECTION_CLOCKWISE);
    ASSERT_EQ(config.timedRotationInMillis, ROTATION_TIME);
}
}