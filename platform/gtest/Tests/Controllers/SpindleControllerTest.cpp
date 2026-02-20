#include "application/System/Controllers/SpindleController/SpindleController.hpp"

#include "application/System/Controllers/PersistentStorageController/PersistentData/SpindlePersistentConfig.hpp"
#include "platform/gtest/Mocks/Controllers/LoggerSinkMock.hpp"
#include "platform/gtest/Mocks/Drivers/MotorDriverMock.hpp"
#include "platform/gtest/Mocks/Ports/SystemClockMock.hpp"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

using namespace testing;

namespace ATC {
class SpindleControllerTest : public Test {
public:
    static constexpr SpindlePersistentConfig SPINDLE_PERSISTENT_CONFIG {
        .speedPercent = 80,
        .isDirectionClockwise = true,
        .timedRotationInMillis = 100
    };

    LoggerSinkMock loggerSinkMock_ {};
    SystemClockMock systemClockMock_ {};
    MotorDriverMock motorDriverMock_ {};

    SpindleController spindleController_ {
        loggerSinkMock_,
        systemClockMock_,
        motorDriverMock_
    };
};

TEST_F(
    SpindleControllerTest,
    GIVEN_spindleController_WHEN_controllerIsInitializedWithClockwiseConfig_THEN_motorDriverIsSetUp
) {
    SpindlePersistentConfig config = SPINDLE_PERSISTENT_CONFIG;
    config.isDirectionClockwise = true;

    {
        InSequence sequence;
        EXPECT_CALL(motorDriverMock_, init());
        EXPECT_CALL(motorDriverMock_, setDirectionClockwise());
    }

    spindleController_.init(config);
}

TEST_F(
    SpindleControllerTest,
    GIVEN_spindleController_WHEN_controllerIsInitializedWithCounterClockwiseConfig_THEN_motorDriverIsSetUp
) {
    SpindlePersistentConfig config = SPINDLE_PERSISTENT_CONFIG;
    config.isDirectionClockwise = false;

    {
        InSequence sequence;
        EXPECT_CALL(motorDriverMock_, init());
        EXPECT_CALL(motorDriverMock_, setDirectionCounterClockwise());
    }

    spindleController_.init(config);
}

TEST_F(
    SpindleControllerTest,
    GIVEN_spindleController_WHEN_controllerIsTicked_THEN_driverFaultIsCheckedUntilReported
) {
    ASSERT_FALSE(spindleController_.wasFaultReported());

    EXPECT_CALL(motorDriverMock_, isFaultDetected())
        .WillOnce(Return(false))
        .WillOnce(Return(false))
        .WillOnce(Return(true));

    constexpr uint8_t tickAmount = 10;
    for (uint8_t i = 0; i < tickAmount; i++) {
        spindleController_.tick();
    }

    ASSERT_TRUE(spindleController_.wasFaultReported());
}

TEST_F(
    SpindleControllerTest,
    GIVEN_spindleController_WHEN_startRotationIsCalled_THEN_motorDriverStartsRotatingWithGivenSpeed
) {
    constexpr uint8_t speedPercent = 35;

    EXPECT_CALL(motorDriverMock_, startRotation(speedPercent));

    spindleController_.setSpeedPercent(speedPercent);
    spindleController_.startRotation();
}

TEST_F(
    SpindleControllerTest,
    GIVEN_spindleController_WHEN_startTimedRotationIsCalledWithParameter_THEN_motorDriverStartsRotatingWithGivenSpeedForGivenTime
) {
    constexpr uint8_t speedPercent = 35;
    constexpr uint32_t rotationMicroseconds = 245;

    {
        InSequence sequence;

        EXPECT_CALL(systemClockMock_, getMillisecondsSinceStart())
            .WillOnce(Return(0));

        EXPECT_CALL(motorDriverMock_, startRotation(speedPercent));
        EXPECT_CALL(systemClockMock_, getMillisecondsSinceStart())
            .WillOnce(Return(rotationMicroseconds * 1 / 3))
            .WillOnce(Return(rotationMicroseconds * 2 / 3))
            .WillOnce(Return(rotationMicroseconds * 3 / 3));
        EXPECT_CALL(motorDriverMock_, stopRotation());
    }

    spindleController_.setSpeedPercent(speedPercent);
    spindleController_.startTimedRotation(rotationMicroseconds);

    constexpr uint8_t tickAmount = 10;
    for (uint8_t i = 0; i < tickAmount; i++) {
        spindleController_.tick();
    }
}

TEST_F(
    SpindleControllerTest,
    GIVEN_spindleController_WHEN_startTimedRotationIsCalled_THEN_motorDriverStartsRotatingWithGivenSpeedForGivenTime
) {
    constexpr uint8_t speedPercent = 35;
    constexpr uint32_t rotationMicroseconds =
        SPINDLE_PERSISTENT_CONFIG.timedRotationInMillis;

    spindleController_.init(SPINDLE_PERSISTENT_CONFIG);

    {
        InSequence sequence;

        EXPECT_CALL(systemClockMock_, getMillisecondsSinceStart())
            .WillOnce(Return(0));

        EXPECT_CALL(motorDriverMock_, startRotation(speedPercent));
        EXPECT_CALL(systemClockMock_, getMillisecondsSinceStart())
            .WillOnce(Return(rotationMicroseconds * 1 / 3))
            .WillOnce(Return(rotationMicroseconds * 2 / 3))
            .WillOnce(Return(rotationMicroseconds * 3 / 3));
        EXPECT_CALL(motorDriverMock_, stopRotation());
    }

    spindleController_.setSpeedPercent(speedPercent);
    spindleController_.startTimedRotation();

    constexpr uint8_t tickAmount = 10;
    for (uint8_t i = 0; i < tickAmount; i++) {
        spindleController_.tick();
    }
}

TEST_F(
    SpindleControllerTest,
    GIVEN_spindleController_WHEN_isTimedRotationFinishedIsCalled_THEN_timedRotationStatusIsReturned
) {
    spindleController_.init(SPINDLE_PERSISTENT_CONFIG);

    ASSERT_TRUE(spindleController_.isTimedRotationFinished());

    EXPECT_CALL(systemClockMock_, getMillisecondsSinceStart())
        .WillOnce(Return(0));
    spindleController_.startTimedRotation();

    ASSERT_FALSE(spindleController_.isTimedRotationFinished());

    EXPECT_CALL(systemClockMock_, getMillisecondsSinceStart())
        .WillOnce(
            Return(SPINDLE_PERSISTENT_CONFIG.timedRotationInMillis)
        );

    spindleController_.tick();

    ASSERT_TRUE(spindleController_.isTimedRotationFinished());

    constexpr uint8_t tickAmount = 10;
    for (uint8_t i = 0; i < tickAmount; i++) {
        spindleController_.tick();
    }
}

TEST_F(
    SpindleControllerTest,
    GIVEN_spindleController_WHEN_stopRotationIsCalled_THEN_motorDriverStopsRotating
) {
    EXPECT_CALL(motorDriverMock_, stopRotation());

    spindleController_.stopRotation();
}

TEST_F(
    SpindleControllerTest,
    GIVEN_spindleController_WHEN_setDirectionClockwiseIsCalled_THEN_motorDriverSetsDirection
) {
    EXPECT_CALL(motorDriverMock_, setDirectionClockwise());

    spindleController_.setDirectionClockwise();
}

TEST_F(
    SpindleControllerTest,
    GIVEN_spindleController_WHEN_setDirectionCounterClockwiseIsCalled_THEN_motorDriverSetsDirection
) {
    EXPECT_CALL(motorDriverMock_, setDirectionCounterClockwise());

    spindleController_.setDirectionCounterClockwise();
}

TEST_F(
    SpindleControllerTest,
    GIVEN_spindleController_WHEN_isDirectionClockwiseIsCalled_THEN_motorDriverDirectionStateIsReturned
) {
    ON_CALL(motorDriverMock_, isDirectionClockwise())
        .WillByDefault(Return(false));

    ASSERT_FALSE(spindleController_.isDirectionClockwise());

    ON_CALL(motorDriverMock_, isDirectionClockwise())
        .WillByDefault(Return(true));

    ASSERT_TRUE(spindleController_.isDirectionClockwise());
}

TEST_F(
    SpindleControllerTest,
    GIVEN_spindleController_WHEN_setSpeedIsCalled_THEN_speedPercentageIsSet
) {
    constexpr uint8_t speedPercent = 65;

    spindleController_.setSpeedPercent(speedPercent);
    ASSERT_EQ(spindleController_.getSpeedPercent(), speedPercent);

    EXPECT_CALL(motorDriverMock_, startRotation(speedPercent));
    spindleController_.startRotation();
}

TEST_F(
    SpindleControllerTest,
    GIVEN_spindleController_WHEN_setRotationTimeIsCalled_THEN_rotationTimeInMillisIsSet
) {
    constexpr uint32_t rotationTimeInMillis = 890;

    spindleController_.setRotationTimeInMillis(rotationTimeInMillis);
    ASSERT_EQ(
        spindleController_.getRotationTimeInMillis(), rotationTimeInMillis
    );

    EXPECT_CALL(systemClockMock_, getMillisecondsSinceStart())
        .WillOnce(Return(0));
    spindleController_.startTimedRotation();

    ASSERT_FALSE(spindleController_.isTimedRotationFinished());

    EXPECT_CALL(systemClockMock_, getMillisecondsSinceStart())
        .WillOnce(Return(rotationTimeInMillis));

    spindleController_.tick();

    ASSERT_TRUE(spindleController_.isTimedRotationFinished());
}
}