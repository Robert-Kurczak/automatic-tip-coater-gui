#include "application/System/Tasks/Task/AxisTestTask/AxisTestTask.hpp"

#include "application/System/Tasks/Task/AxisTestTask/AxisTestResults.hpp"
#include "platform/gtest/Mocks/Controllers/AxisControllerMock.hpp"
#include "platform/gtest/Mocks/Ports/SystemClockMock.hpp"
#include "platform/gtest/Mocks/Tasks/ConsumableTaskMock.hpp"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

using namespace testing;

namespace ATC {
class AxisTestTaskTest : public Test {
public:
    static constexpr uint8_t TICK_AMOUNT = 200;

    ConsumableTaskMock<bool> calibrationTaskMock_ {};
    AxisControllerMock axisControllerMock_ {};
    SystemClockMock systemClockMock_ {};
    static constexpr uint32_t AXIS_MOVE_TIMEOUT_IN_MILLIS = 5000;

    AxisTestTask axisTestTask_ {
        calibrationTaskMock_,
        axisControllerMock_,
        systemClockMock_,
        AXIS_MOVE_TIMEOUT_IN_MILLIS
    };

    void expectClockSimulation() {
        EXPECT_CALL(systemClockMock_, getMillisecondsSinceStart())
            .WillRepeatedly([]() {
                constexpr uint32_t millisBetweenCalls = 100;
                static uint32_t calls = 0;

                calls++;

                return millisBetweenCalls * calls;
            });
    }
};

TEST_F(
    AxisTestTaskTest,
    GIVEN_axisTestTask_WHEN_taskIsNotStarted_THEN_taskIdlesWhenTicked
) {
    EXPECT_CALL(axisControllerMock_, moveToMinLimitPosition()).Times(0);
    EXPECT_CALL(axisControllerMock_, moveToMaxLimitPosition()).Times(0);

    for (uint8_t i = 0; i < TICK_AMOUNT; i++) {
        axisTestTask_.tick();
    }
}

TEST_F(
    AxisTestTaskTest,
    GIVEN_axisTestTask_WHEN_taskIsStarted_THEN_calibrationTaskIsExecuted
) {
    EXPECT_CALL(calibrationTaskMock_, isFinished())
        .WillOnce(Return(false))
        .WillOnce(Return(false))
        .WillRepeatedly(Return(true));

    {
        InSequence seq;

        EXPECT_CALL(calibrationTaskMock_, start());

        EXPECT_CALL(calibrationTaskMock_, tick()).Times(AtLeast(3));

        EXPECT_CALL(calibrationTaskMock_, consumeResult())
            .WillOnce(Return(true));
    }

    axisTestTask_.start();

    for (uint8_t i = 0; i < TICK_AMOUNT; i++) {
        axisTestTask_.tick();
    }
}

TEST_F(
    AxisTestTaskTest,
    GIVEN_axisTestTask_WHEN_calibrationFails_THEN_taskFinishes
) {
    EXPECT_CALL(calibrationTaskMock_, isFinished())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(calibrationTaskMock_, consumeResult())
        .WillOnce(Return(false));

    axisTestTask_.start();

    ASSERT_FALSE(axisTestTask_.isFinished());

    for (uint8_t i = 0; i < TICK_AMOUNT; i++) {
        axisTestTask_.tick();
    }

    ASSERT_TRUE(axisTestTask_.isFinished());
}

TEST_F(
    AxisTestTaskTest,
    GIVEN_axisTestTask_WHEN_calibrationSucceed_THEN_axisIsMovedToMinPosition
) {
    EXPECT_CALL(calibrationTaskMock_, isFinished())
        .WillRepeatedly(Return(true));

    {
        InSequence sequence;
        EXPECT_CALL(calibrationTaskMock_, consumeResult())
            .WillOnce(Return(true));

        EXPECT_CALL(axisControllerMock_, moveToMinLimitPosition());
    }

    axisTestTask_.start();

    ASSERT_FALSE(axisTestTask_.isFinished());

    for (uint8_t i = 0; i < TICK_AMOUNT; i++) {
        axisTestTask_.tick();
    }

    ASSERT_FALSE(axisTestTask_.isFinished());
}

TEST_F(
    AxisTestTaskTest,
    GIVEN_axisTestTask_WHEN_axisReachesMinPosition_THEN_axisIsMovedToMaxPosition
) {
    EXPECT_CALL(calibrationTaskMock_, isFinished())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(calibrationTaskMock_, consumeResult())
        .WillOnce(Return(true));

    {
        InSequence sequence;

        EXPECT_CALL(axisControllerMock_, isAtMinLimitPosition())
            .WillOnce(Return(true));

        EXPECT_CALL(axisControllerMock_, moveToMaxLimitPosition());
    }

    axisTestTask_.start();

    for (uint8_t i = 0; i < TICK_AMOUNT; i++) {
        axisTestTask_.tick();
    }
}

TEST_F(
    AxisTestTaskTest,
    GIVEN_axisTestTask_WHEN_axisReachesMaxPosition_THEN_taskIsFinished
) {
    EXPECT_CALL(calibrationTaskMock_, isFinished())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(calibrationTaskMock_, consumeResult())
        .WillOnce(Return(true));

    EXPECT_CALL(axisControllerMock_, isAtMinLimitPosition())
        .WillOnce(Return(true));

    EXPECT_CALL(axisControllerMock_, isAtMaxLimitPosition())
        .WillOnce(Return(true));

    axisTestTask_.start();

    for (uint8_t i = 0; i < TICK_AMOUNT; i++) {
        axisTestTask_.tick();
    }

    ASSERT_TRUE(axisTestTask_.isFinished());
}

TEST_F(
    AxisTestTaskTest,
    GIVEN_axisTestTask_WHEN_reachingMinPositionTimesOut_THEN_minLimitSwitchFailureIsReported
) {
    EXPECT_CALL(calibrationTaskMock_, isFinished())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(calibrationTaskMock_, consumeResult())
        .WillOnce(Return(true));

    EXPECT_CALL(axisControllerMock_, isAtMinLimitPosition())
        .WillRepeatedly(Return(false));

    expectClockSimulation();

    axisTestTask_.start();

    for (uint8_t i = 0; i < TICK_AMOUNT; i++) {
        axisTestTask_.tick();
    }

    ASSERT_TRUE(axisTestTask_.isFinished());
    const AxisTestResults results = axisTestTask_.consumeResult();

    ASSERT_FALSE(results.startLimitSwitchSuccess);
}

TEST_F(
    AxisTestTaskTest,
    GIVEN_axisTestTask_WHEN_axisReachesMinPosition_THEN_minLimitSwitchSuccessIsReported
) {
    EXPECT_CALL(calibrationTaskMock_, isFinished())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(calibrationTaskMock_, consumeResult())
        .WillOnce(Return(true));

    EXPECT_CALL(axisControllerMock_, isAtMinLimitPosition())
        .WillOnce(Return(true));

    expectClockSimulation();

    axisTestTask_.start();

    for (uint8_t i = 0; i < TICK_AMOUNT; i++) {
        axisTestTask_.tick();
    }

    ASSERT_TRUE(axisTestTask_.isFinished());
    const AxisTestResults results = axisTestTask_.consumeResult();

    ASSERT_TRUE(results.startLimitSwitchSuccess);
}

TEST_F(
    AxisTestTaskTest,
    GIVEN_axisTestTask_WHEN_reachingMaxPositionTimesOut_THEN_maxLimitSwitchFailureIsReported
) {
    EXPECT_CALL(calibrationTaskMock_, isFinished())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(calibrationTaskMock_, consumeResult())
        .WillOnce(Return(true));

    EXPECT_CALL(axisControllerMock_, isAtMinLimitPosition())
        .WillOnce(Return(true));

    EXPECT_CALL(axisControllerMock_, isAtMaxLimitPosition())
        .WillRepeatedly(Return(false));

    expectClockSimulation();

    axisTestTask_.start();

    for (uint8_t i = 0; i < TICK_AMOUNT; i++) {
        axisTestTask_.tick();
    }

    ASSERT_TRUE(axisTestTask_.isFinished());
    const AxisTestResults results = axisTestTask_.consumeResult();

    ASSERT_FALSE(results.endLimitSwitchSuccess);
}

TEST_F(
    AxisTestTaskTest,
    GIVEN_axisTestTask_WHEN_axisReachesMaxPosition_THEN_maxLimitSwitchSuccessIsReported
) {
    EXPECT_CALL(calibrationTaskMock_, isFinished())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(calibrationTaskMock_, consumeResult())
        .WillOnce(Return(true));

    EXPECT_CALL(axisControllerMock_, isAtMinLimitPosition())
        .WillOnce(Return(true));

    EXPECT_CALL(axisControllerMock_, isAtMaxLimitPosition())
        .WillOnce(Return(true));

    expectClockSimulation();

    axisTestTask_.start();

    for (uint8_t i = 0; i < TICK_AMOUNT; i++) {
        axisTestTask_.tick();
    }

    ASSERT_TRUE(axisTestTask_.isFinished());
    const AxisTestResults results = axisTestTask_.consumeResult();

    ASSERT_TRUE(results.endLimitSwitchSuccess);
}

TEST_F(
    AxisTestTaskTest,
    GIVEN_axisTestTask_WHEN_controllerFaultWasReported_THEN_motorDriverFailureIsReported
) {
    EXPECT_CALL(calibrationTaskMock_, isFinished())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(calibrationTaskMock_, consumeResult())
        .WillOnce(Return(true));

    EXPECT_CALL(axisControllerMock_, isAtMinLimitPosition())
        .WillOnce(Return(true));

    EXPECT_CALL(axisControllerMock_, isAtMaxLimitPosition())
        .WillOnce(Return(true));

    EXPECT_CALL(axisControllerMock_, wasFaultReported())
        .WillRepeatedly(Return(true));

    axisTestTask_.start();

    for (uint8_t i = 0; i < TICK_AMOUNT; i++) {
        axisTestTask_.tick();
    }

    ASSERT_TRUE(axisTestTask_.isFinished());
    const AxisTestResults results = axisTestTask_.consumeResult();

    ASSERT_FALSE(results.motorDriverSuccess);
}

TEST_F(
    AxisTestTaskTest,
    GIVEN_axisTestTask_WHEN_controllerFaultWasNotReported_THEN_motorDriverSuccessIsReported
) {
    EXPECT_CALL(calibrationTaskMock_, isFinished())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(calibrationTaskMock_, consumeResult())
        .WillOnce(Return(true));

    EXPECT_CALL(axisControllerMock_, isAtMinLimitPosition())
        .WillOnce(Return(true));

    EXPECT_CALL(axisControllerMock_, isAtMaxLimitPosition())
        .WillOnce(Return(true));

    EXPECT_CALL(axisControllerMock_, wasFaultReported())
        .WillRepeatedly(Return(false));

    axisTestTask_.start();

    for (uint8_t i = 0; i < TICK_AMOUNT; i++) {
        axisTestTask_.tick();
    }

    ASSERT_TRUE(axisTestTask_.isFinished());
    const AxisTestResults results = axisTestTask_.consumeResult();

    ASSERT_TRUE(results.motorDriverSuccess);
}

TEST_F(
    AxisTestTaskTest,
    GIVEN_axisTestTask_WHEN_taskIsReset_THEN_movementIsCanceled
) {
    axisTestTask_.start();

    EXPECT_CALL(axisControllerMock_, cancelMovement());

    axisTestTask_.reset();
}

TEST_F(
    AxisTestTaskTest,
    GIVEN_axisTestTask_WHEN_resultIsConsumed_THEN_resultsAreReset
) {
    EXPECT_CALL(calibrationTaskMock_, isFinished())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(calibrationTaskMock_, consumeResult())
        .WillOnce(Return(true));

    EXPECT_CALL(axisControllerMock_, isAtMinLimitPosition())
        .WillOnce(Return(true));

    EXPECT_CALL(axisControllerMock_, isAtMaxLimitPosition())
        .WillOnce(Return(true));

    EXPECT_CALL(axisControllerMock_, wasFaultReported())
        .WillRepeatedly(Return(false));

    axisTestTask_.start();

    for (uint8_t i = 0; i < TICK_AMOUNT; i++) {
        axisTestTask_.tick();
    }

    ASSERT_TRUE(axisTestTask_.isFinished());

    const AxisTestResults successfulResults =
        axisTestTask_.consumeResult();

    const AxisTestResults cleanedResults = axisTestTask_.consumeResult();

    ASSERT_FALSE(cleanedResults.startLimitSwitchSuccess);
    ASSERT_FALSE(cleanedResults.endLimitSwitchSuccess);
    ASSERT_FALSE(cleanedResults.motorDriverSuccess);
}
}