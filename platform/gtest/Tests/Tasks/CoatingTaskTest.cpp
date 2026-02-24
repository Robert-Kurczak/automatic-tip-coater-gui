#include "application/System/Tasks/Task/CoatingTask/CoatingTask.hpp"

#include "platform/gtest/Mocks/Controllers/AxisControllerMock.hpp"
#include "platform/gtest/Mocks/Controllers/HeaterControllerMock.hpp"
#include "platform/gtest/Mocks/Controllers/SpindleControllerMock.hpp"
#include "platform/gtest/Mocks/Tasks/ConsumableTaskMock.hpp"

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <sys/wait.h>

using namespace testing;

namespace ATC {
class CoatingTaskTest : public Test {
public:
    static constexpr uint8_t TICK_AMOUNT = 200;

    ConsumableTaskMock<bool> calibrationTaskMock_ {};
    XAxisControllerMock xAxisControllerMock_ {};
    YAxisControllerMock yAxisControllerMock_ {};
    ZAxisControllerMock zAxisControllerMock_ {};
    SpindleControllerMock spindleControllerMock_ {};
    HeaterControllerMock heaterControllerMock_ {};

    CoatingTask coatingTask_ {
        calibrationTaskMock_,
        xAxisControllerMock_,
        yAxisControllerMock_,
        zAxisControllerMock_,
        spindleControllerMock_,
        heaterControllerMock_
    };
};

TEST_F(
    CoatingTaskTest,
    GIVEN_coatingTask_WHEN_taskIsNotStarted_THEN_taskIdlesWhenTicked
) {
    EXPECT_CALL(heaterControllerMock_, turnOn()).Times(0);
    EXPECT_CALL(xAxisControllerMock_, moveToHeaterFrontPosition())
        .Times(0);
    EXPECT_CALL(yAxisControllerMock_, moveToStartPosition()).Times(0);
    EXPECT_CALL(zAxisControllerMock_, moveToStartPosition()).Times(0);

    for (uint8_t i = 0; i < TICK_AMOUNT; i++) {
        coatingTask_.tick();
    }
}

TEST_F(
    CoatingTaskTest,
    GIVEN_coatingTask_WHEN_taskIsStarted_THEN_calibrationTaskIsExecuted
) {
    EXPECT_CALL(calibrationTaskMock_, isFinished())
        .WillOnce(Return(false))
        .WillOnce(Return(false))
        .WillRepeatedly(Return(true));

    {
        InSequence sequence;

        EXPECT_CALL(calibrationTaskMock_, start());

        EXPECT_CALL(calibrationTaskMock_, tick()).Times(AtLeast(3));

        EXPECT_CALL(calibrationTaskMock_, consumeResult())
            .WillOnce(Return(true));
    }

    coatingTask_.start();

    for (uint8_t i = 0; i < TICK_AMOUNT; i++) {
        coatingTask_.tick();
    }
}

TEST_F(
    CoatingTaskTest,
    GIVEN_coatingTask_WHEN_calibrationFails_THEN_taskFinishes
) {
    EXPECT_CALL(calibrationTaskMock_, isFinished())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(calibrationTaskMock_, consumeResult())
        .WillOnce(Return(false));

    coatingTask_.start();

    ASSERT_FALSE(coatingTask_.isFinished());

    for (uint8_t i = 0; i < TICK_AMOUNT; i++) {
        coatingTask_.tick();
    }

    ASSERT_TRUE(coatingTask_.isFinished());
}

TEST_F(
    CoatingTaskTest,
    GIVEN_coatingTask_WHEN_calibrationSucceed_THEN_heaterIsTurnedOn
) {
    EXPECT_CALL(calibrationTaskMock_, isFinished())
        .WillRepeatedly(Return(true));

    {
        InSequence sequence;
        EXPECT_CALL(calibrationTaskMock_, consumeResult())
            .WillOnce(Return(true));

        EXPECT_CALL(heaterControllerMock_, turnOn());
    }

    coatingTask_.start();

    ASSERT_FALSE(coatingTask_.isFinished());

    for (uint8_t i = 0; i < TICK_AMOUNT; i++) {
        coatingTask_.tick();
    }

    ASSERT_FALSE(coatingTask_.isFinished());
}

TEST_F(
    CoatingTaskTest,
    GIVEN_coatingTask_WHEN_heaterIsTurnedOn_THEN_axesAreMovedToInitialPositions
) {
    EXPECT_CALL(calibrationTaskMock_, isFinished())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(calibrationTaskMock_, consumeResult())
        .WillOnce(Return(true));

    ExpectationSet initialExpectations;

    initialExpectations += EXPECT_CALL(heaterControllerMock_, turnOn());

    EXPECT_CALL(xAxisControllerMock_, moveToHeaterFrontPosition())
        .After(initialExpectations);

    EXPECT_CALL(yAxisControllerMock_, moveToStartPosition())
        .After(initialExpectations);

    EXPECT_CALL(zAxisControllerMock_, moveToStartPosition())
        .After(initialExpectations);

    coatingTask_.start();

    for (uint8_t i = 0; i < TICK_AMOUNT; i++) {
        coatingTask_.tick();
    }
}

TEST_F(
    CoatingTaskTest,
    GIVEN_coatingTask_WHEN_axesAreAtInitialPositions_THEN_zAxisIsMovedToEndPosition
) {
    EXPECT_CALL(calibrationTaskMock_, isFinished())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(calibrationTaskMock_, consumeResult())
        .WillOnce(Return(true));

    ExpectationSet initialExpectations;

    initialExpectations +=
        EXPECT_CALL(xAxisControllerMock_, isAtHeaterFrontPosition())
            .WillOnce(Return(false))
            .WillRepeatedly(Return(true));

    initialExpectations +=
        EXPECT_CALL(yAxisControllerMock_, isAtStartPosition())
            .WillOnce(Return(false))
            .WillOnce(Return(false))
            .WillRepeatedly(Return(true));

    initialExpectations +=
        EXPECT_CALL(zAxisControllerMock_, isAtStartPosition())
            .WillOnce(Return(false))
            .WillOnce(Return(false))
            .WillOnce(Return(false))
            .WillRepeatedly(Return(true));

    EXPECT_CALL(zAxisControllerMock_, moveToEndPosition())
        .After(initialExpectations);

    coatingTask_.start();

    for (uint8_t i = 0; i < TICK_AMOUNT; i++) {
        coatingTask_.tick();
    }
}

TEST_F(
    CoatingTaskTest,
    GIVEN_coatingTask_WHEN_zAxisIsAtEndPosition_THEN_yAxisDetectsTip
) {
    EXPECT_CALL(calibrationTaskMock_, isFinished())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(calibrationTaskMock_, consumeResult())
        .WillOnce(Return(true));

    EXPECT_CALL(xAxisControllerMock_, isAtHeaterFrontPosition())
        .WillOnce(Return(true));

    EXPECT_CALL(yAxisControllerMock_, isAtStartPosition())
        .WillOnce(Return(true));

    EXPECT_CALL(zAxisControllerMock_, isAtStartPosition())
        .WillOnce(Return(true));

    ExpectationSet initialExpectations;

    initialExpectations +=
        EXPECT_CALL(zAxisControllerMock_, isAtEndPosition())
            .WillOnce(Return(false))
            .WillOnce(Return(false))
            .WillRepeatedly(Return(true));

    EXPECT_CALL(yAxisControllerMock_, moveToDetectTip())
        .After(initialExpectations);

    coatingTask_.start();

    for (uint8_t i = 0; i < TICK_AMOUNT; i++) {
        coatingTask_.tick();
    }
}

TEST_F(
    CoatingTaskTest,
    GIVEN_coatingTask_WHEN_yAxisDetectedTip_THEN_yAxisIsMovedIntoCoatingPosition
) {
    EXPECT_CALL(calibrationTaskMock_, isFinished())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(calibrationTaskMock_, consumeResult())
        .WillOnce(Return(true));

    EXPECT_CALL(xAxisControllerMock_, isAtHeaterFrontPosition())
        .WillOnce(Return(true));

    EXPECT_CALL(yAxisControllerMock_, isAtStartPosition())
        .WillOnce(Return(true));

    EXPECT_CALL(zAxisControllerMock_, isAtStartPosition())
        .WillOnce(Return(true));

    EXPECT_CALL(zAxisControllerMock_, isAtEndPosition())
        .WillOnce(Return(true));

    ExpectationSet initialExpectations;

    initialExpectations +=
        EXPECT_CALL(yAxisControllerMock_, isTipDetected())
            .WillOnce(Return(false))
            .WillOnce(Return(false))
            .WillRepeatedly(Return(true));

    EXPECT_CALL(yAxisControllerMock_, moveToCoatingPosition());

    coatingTask_.start();

    for (uint8_t i = 0; i < TICK_AMOUNT; i++) {
        coatingTask_.tick();
    }
}

TEST_F(
    CoatingTaskTest,
    GIVEN_coatingTask_WHEN_yAxisIsAtCoatingPosition_THEN_zAxisIsMovedToStartPosition
) {
    EXPECT_CALL(calibrationTaskMock_, isFinished())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(calibrationTaskMock_, consumeResult())
        .WillOnce(Return(true));

    EXPECT_CALL(xAxisControllerMock_, isAtHeaterFrontPosition())
        .WillOnce(Return(true));

    EXPECT_CALL(yAxisControllerMock_, isAtStartPosition())
        .WillOnce(Return(true));

    EXPECT_CALL(zAxisControllerMock_, isAtStartPosition())
        .WillOnce(Return(true))
        .WillRepeatedly(Return(false));

    EXPECT_CALL(zAxisControllerMock_, isAtEndPosition())
        .WillOnce(Return(true));

    EXPECT_CALL(yAxisControllerMock_, isTipDetected())
        .WillOnce(Return(true));

    ExpectationSet initialExpectations;

    EXPECT_CALL(zAxisControllerMock_, moveToStartPosition());

    initialExpectations +=
        EXPECT_CALL(yAxisControllerMock_, isAtCoatingPosition())
            .WillOnce(Return(false))
            .WillOnce(Return(false))
            .WillRepeatedly(Return(true));

    EXPECT_CALL(zAxisControllerMock_, moveToStartPosition())
        .After(initialExpectations);

    coatingTask_.start();

    for (uint8_t i = 0; i < TICK_AMOUNT; i++) {
        coatingTask_.tick();
    }
}

TEST_F(
    CoatingTaskTest,
    GIVEN_coatingTask_WHEN_zAxisIsAtStartPosition_THEN_xAxisIsMovedToEndPosition
) {
    EXPECT_CALL(calibrationTaskMock_, isFinished())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(calibrationTaskMock_, consumeResult())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(xAxisControllerMock_, isAtHeaterFrontPosition())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(yAxisControllerMock_, isAtStartPosition())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(zAxisControllerMock_, isAtStartPosition())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(zAxisControllerMock_, isAtEndPosition())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(yAxisControllerMock_, isTipDetected())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(yAxisControllerMock_, isAtCoatingPosition())
        .WillRepeatedly(Return(true));

    ExpectationSet initialExpectations;

    initialExpectations +=
        EXPECT_CALL(zAxisControllerMock_, isAtStartPosition())
            .WillOnce(Return(false))
            .WillOnce(Return(false))
            .WillRepeatedly(Return(true));

    EXPECT_CALL(xAxisControllerMock_, moveToEndPosition())
        .After(initialExpectations);

    coatingTask_.start();

    for (uint8_t i = 0; i < TICK_AMOUNT; i++) {
        coatingTask_.tick();
    }
}

TEST_F(
    CoatingTaskTest,
    GIVEN_coatingTask_WHEN_xAxisIsAtEndPosition_THEN_taskWaitsForHeaterTemperature
) {
    EXPECT_CALL(calibrationTaskMock_, isFinished())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(calibrationTaskMock_, consumeResult())
        .WillOnce(Return(true));

    EXPECT_CALL(xAxisControllerMock_, isAtHeaterFrontPosition())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(yAxisControllerMock_, isAtStartPosition())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(zAxisControllerMock_, isAtStartPosition())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(zAxisControllerMock_, isAtEndPosition())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(yAxisControllerMock_, isTipDetected())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(yAxisControllerMock_, isAtCoatingPosition())
        .WillRepeatedly(Return(true));

    ExpectationSet initialExpectations;

    initialExpectations +=
        EXPECT_CALL(xAxisControllerMock_, isAtEndPosition())
            .WillOnce(Return(false))
            .WillOnce(Return(false))
            .WillRepeatedly(Return(true));

    EXPECT_CALL(heaterControllerMock_, isAtTargetTemperature())
        .Times(AtLeast(1))
        .After(initialExpectations);

    coatingTask_.start();

    for (uint8_t i = 0; i < TICK_AMOUNT; i++) {
        coatingTask_.tick();
    }
}

TEST_F(
    CoatingTaskTest,
    GIVEN_coatingTask_WHEN_heaterReachesTargetTemperature_THEN_rotationIsStarted
) {
    EXPECT_CALL(calibrationTaskMock_, isFinished())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(calibrationTaskMock_, consumeResult())
        .WillOnce(Return(true));

    EXPECT_CALL(xAxisControllerMock_, isAtHeaterFrontPosition())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(yAxisControllerMock_, isAtStartPosition())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(zAxisControllerMock_, isAtStartPosition())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(zAxisControllerMock_, isAtEndPosition())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(yAxisControllerMock_, isTipDetected())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(yAxisControllerMock_, isAtCoatingPosition())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(xAxisControllerMock_, isAtEndPosition())
        .WillRepeatedly(Return(true));

    ExpectationSet initialExpectations;

    initialExpectations +=
        EXPECT_CALL(heaterControllerMock_, isAtTargetTemperature())
            .WillOnce(Return(false))
            .WillOnce(Return(false))
            .WillRepeatedly(Return(true));

    EXPECT_CALL(spindleControllerMock_, startRotation())
        .Times(AtLeast(1))
        .After(initialExpectations);

    coatingTask_.start();

    for (uint8_t i = 0; i < TICK_AMOUNT; i++) {
        coatingTask_.tick();
    }
}

TEST_F(
    CoatingTaskTest,
    GIVEN_coatingTask_WHEN_rotationIsStarted_THEN_xAxisIsMovedToHeaterFrontPosition
) {
    EXPECT_CALL(calibrationTaskMock_, isFinished())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(calibrationTaskMock_, consumeResult())
        .WillOnce(Return(true));

    EXPECT_CALL(xAxisControllerMock_, moveToHeaterFrontPosition());
    EXPECT_CALL(xAxisControllerMock_, isAtHeaterFrontPosition())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(yAxisControllerMock_, isAtStartPosition())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(zAxisControllerMock_, isAtStartPosition())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(zAxisControllerMock_, isAtEndPosition())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(yAxisControllerMock_, isTipDetected())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(yAxisControllerMock_, isAtCoatingPosition())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(xAxisControllerMock_, isAtEndPosition())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(heaterControllerMock_, isAtTargetTemperature())
        .WillRepeatedly(Return(true));

    ExpectationSet initialExpectations;

    initialExpectations +=
        EXPECT_CALL(spindleControllerMock_, startRotation());

    EXPECT_CALL(xAxisControllerMock_, moveToHeaterFrontPosition())
        .After(initialExpectations);

    coatingTask_.start();

    for (uint8_t i = 0; i < TICK_AMOUNT; i++) {
        coatingTask_.tick();
    }
}

TEST_F(
    CoatingTaskTest,
    GIVEN_coatingTask_WHEN_xAxisReachesHeaterFrontPosition_THEN_timedRotationIsStarted
) {
    EXPECT_CALL(calibrationTaskMock_, isFinished())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(calibrationTaskMock_, consumeResult())
        .WillOnce(Return(true));

    EXPECT_CALL(yAxisControllerMock_, isAtStartPosition())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(zAxisControllerMock_, isAtStartPosition())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(zAxisControllerMock_, isAtEndPosition())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(yAxisControllerMock_, isTipDetected())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(yAxisControllerMock_, isAtCoatingPosition())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(xAxisControllerMock_, isAtEndPosition())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(heaterControllerMock_, isAtTargetTemperature())
        .WillRepeatedly(Return(true));

    ExpectationSet initialExpectations;

    initialExpectations +=
        EXPECT_CALL(xAxisControllerMock_, isAtHeaterFrontPosition())
            .WillOnce(Return(true))
            .WillOnce(Return(false))
            .WillOnce(Return(false))
            .WillOnce(Return(true));

    EXPECT_CALL(spindleControllerMock_, startTimedRotation())
        .After(initialExpectations);

    coatingTask_.start();

    for (uint8_t i = 0; i < TICK_AMOUNT; i++) {
        coatingTask_.tick();
    }
}

TEST_F(
    CoatingTaskTest,
    GIVEN_coatingTask_WHEN_timedRotationIsFinished_THEN_xAxisIsMovedToStartPosition
) {
    EXPECT_CALL(calibrationTaskMock_, isFinished())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(calibrationTaskMock_, consumeResult())
        .WillOnce(Return(true));

    EXPECT_CALL(xAxisControllerMock_, isAtHeaterFrontPosition())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(yAxisControllerMock_, isAtStartPosition())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(zAxisControllerMock_, isAtStartPosition())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(zAxisControllerMock_, isAtEndPosition())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(yAxisControllerMock_, isTipDetected())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(yAxisControllerMock_, isAtCoatingPosition())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(xAxisControllerMock_, isAtEndPosition())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(heaterControllerMock_, isAtTargetTemperature())
        .WillRepeatedly(Return(true));

    ExpectationSet initialExpectations;

    initialExpectations +=
        EXPECT_CALL(spindleControllerMock_, isTimedRotationFinished())
            .WillOnce(Return(false))
            .WillOnce(Return(false))
            .WillOnce(Return(true));

    EXPECT_CALL(xAxisControllerMock_, moveToStartPosition());

    coatingTask_.start();

    for (uint8_t i = 0; i < TICK_AMOUNT; i++) {
        coatingTask_.tick();
    }
}

TEST_F(
    CoatingTaskTest,
    GIVEN_coatingTask_WHEN_xAxisReachesStartPosition_THEN_heaterIsTurnedOff
) {
    EXPECT_CALL(calibrationTaskMock_, isFinished())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(calibrationTaskMock_, consumeResult())
        .WillOnce(Return(true));

    EXPECT_CALL(xAxisControllerMock_, isAtHeaterFrontPosition())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(yAxisControllerMock_, isAtStartPosition())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(zAxisControllerMock_, isAtStartPosition())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(zAxisControllerMock_, isAtEndPosition())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(yAxisControllerMock_, isTipDetected())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(yAxisControllerMock_, isAtCoatingPosition())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(xAxisControllerMock_, isAtEndPosition())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(heaterControllerMock_, isAtTargetTemperature())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(spindleControllerMock_, isTimedRotationFinished())
        .WillRepeatedly(Return(true));

    ExpectationSet initialExpectations;

    initialExpectations +=
        EXPECT_CALL(xAxisControllerMock_, isAtStartPosition())
            .WillOnce(Return(false))
            .WillOnce(Return(false))
            .WillOnce(Return(true));

    EXPECT_CALL(heaterControllerMock_, turnOff())
        .After(initialExpectations);

    coatingTask_.start();

    for (uint8_t i = 0; i < TICK_AMOUNT; i++) {
        coatingTask_.tick();
    }
}

TEST_F(
    CoatingTaskTest,
    GIVEN_coatingTask_WHEN_heaterIsTurnedOff_THEN_rotationIsStopped
) {
    EXPECT_CALL(calibrationTaskMock_, isFinished())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(calibrationTaskMock_, consumeResult())
        .WillOnce(Return(true));

    EXPECT_CALL(xAxisControllerMock_, isAtHeaterFrontPosition())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(yAxisControllerMock_, isAtStartPosition())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(zAxisControllerMock_, isAtStartPosition())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(zAxisControllerMock_, isAtEndPosition())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(yAxisControllerMock_, isTipDetected())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(yAxisControllerMock_, isAtCoatingPosition())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(xAxisControllerMock_, isAtEndPosition())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(heaterControllerMock_, isAtTargetTemperature())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(spindleControllerMock_, isTimedRotationFinished())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(xAxisControllerMock_, isAtStartPosition())
        .WillRepeatedly(Return(true));

    ExpectationSet initialExpectations;

    initialExpectations += EXPECT_CALL(heaterControllerMock_, turnOff());

    EXPECT_CALL(spindleControllerMock_, stopRotation())
        .After(initialExpectations);

    coatingTask_.start();

    for (uint8_t i = 0; i < TICK_AMOUNT; i++) {
        coatingTask_.tick();
    }
}

TEST_F(
    CoatingTaskTest,
    GIVEN_coatingTask_WHEN_rotationIsStopped_THEN_taskIsFinished
) {
    EXPECT_CALL(calibrationTaskMock_, isFinished())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(calibrationTaskMock_, consumeResult())
        .WillOnce(Return(true));

    EXPECT_CALL(xAxisControllerMock_, isAtHeaterFrontPosition())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(yAxisControllerMock_, isAtStartPosition())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(zAxisControllerMock_, isAtStartPosition())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(zAxisControllerMock_, isAtEndPosition())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(yAxisControllerMock_, isTipDetected())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(yAxisControllerMock_, isAtCoatingPosition())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(xAxisControllerMock_, isAtEndPosition())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(heaterControllerMock_, isAtTargetTemperature())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(spindleControllerMock_, isTimedRotationFinished())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(xAxisControllerMock_, isAtStartPosition())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(spindleControllerMock_, stopRotation());

    coatingTask_.start();

    ASSERT_FALSE(coatingTask_.isFinished());

    for (uint8_t i = 0; i < TICK_AMOUNT; i++) {
        coatingTask_.tick();
    }

    ASSERT_TRUE(coatingTask_.isFinished());
}

TEST_F(
    CoatingTaskTest,
    GIVEN_coatingTask_WHEN_taskIsReset_THEN_movementIsCanceled
) {
    coatingTask_.start();

    EXPECT_CALL(xAxisControllerMock_, cancelMovement());
    EXPECT_CALL(yAxisControllerMock_, cancelMovement());
    EXPECT_CALL(zAxisControllerMock_, cancelMovement());

    coatingTask_.reset();
}

TEST_F(
    CoatingTaskTest,
    GIVEN_coatingTask_WHEN_taskIsReset_THEN_resultsAreReset
) {
    coatingTask_.start();

    coatingTask_.reset();

    const bool success = coatingTask_.consumeResult();
    ASSERT_FALSE(success);
}

TEST_F(
    CoatingTaskTest,
    GIVEN_coatingTask_WHEN_resultIsConsumed_THEN_resultsAreReset
) {
    EXPECT_CALL(calibrationTaskMock_, isFinished())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(calibrationTaskMock_, consumeResult())
        .WillOnce(Return(true));

    EXPECT_CALL(xAxisControllerMock_, isAtHeaterFrontPosition())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(yAxisControllerMock_, isAtStartPosition())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(zAxisControllerMock_, isAtStartPosition())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(zAxisControllerMock_, isAtEndPosition())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(yAxisControllerMock_, isTipDetected())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(yAxisControllerMock_, isAtCoatingPosition())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(xAxisControllerMock_, isAtEndPosition())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(heaterControllerMock_, isAtTargetTemperature())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(spindleControllerMock_, isTimedRotationFinished())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(xAxisControllerMock_, isAtStartPosition())
        .WillRepeatedly(Return(true));

    coatingTask_.start();

    for (uint8_t i = 0; i < TICK_AMOUNT; i++) {
        coatingTask_.tick();
    }

    const bool successResults = coatingTask_.consumeResult();
    const bool cleanedResults = coatingTask_.consumeResult();

    ASSERT_TRUE(successResults);
    ASSERT_FALSE(cleanedResults);
}
}