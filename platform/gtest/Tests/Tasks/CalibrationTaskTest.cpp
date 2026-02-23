#include "application/System/Tasks/Task/CalibrationTask/CalibrationTask.hpp"

#include "platform/gtest/Mocks/Controllers/AxisControllerMock.hpp"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

using namespace testing;

namespace ATC {
class CalibrationTaskTest : public Test {
public:
    static constexpr uint8_t TICK_AMOUNT = 200;

    XAxisControllerMock xAxisControllerMock_ {};
    YAxisControllerMock yAxisControllerMock_ {};
    ZAxisControllerMock zAxisControllerMock_ {};

    CalibrationTask calibrationTask_ {
        xAxisControllerMock_,
        yAxisControllerMock_,
        zAxisControllerMock_
    };
};

TEST_F(
    CalibrationTaskTest,
    GIVEN_calibrationTask_WHEN_taskIsNotStarted_THEN_taskIdlesWhenTicked
) {
    EXPECT_CALL(xAxisControllerMock_, moveToHomePosition()).Times(0);
    EXPECT_CALL(yAxisControllerMock_, moveToHomePosition()).Times(0);
    EXPECT_CALL(zAxisControllerMock_, moveToHomePosition()).Times(0);

    for (uint8_t i = 0; i < TICK_AMOUNT; i++) {
        calibrationTask_.tick();
    }
}

TEST_F(
    CalibrationTaskTest,
    GIVEN_calibrationTask_WHEN_taskIsStarted_THEN_axesAreHomed
) {
    EXPECT_CALL(xAxisControllerMock_, moveToHomePosition());
    EXPECT_CALL(yAxisControllerMock_, moveToHomePosition());
    EXPECT_CALL(zAxisControllerMock_, moveToHomePosition());

    calibrationTask_.start();

    for (uint8_t i = 0; i < TICK_AMOUNT; i++) {
        calibrationTask_.tick();
    }
}

TEST_F(
    CalibrationTaskTest,
    GIVEN_calibrationTask_WHEN_axesAreHomed_THEN_axesAreMovedToStartPosition
) {
    ExpectationSet initialExpectations;

    initialExpectations +=
        EXPECT_CALL(xAxisControllerMock_, isAtHomePosition())
            .WillOnce(Return(false))
            .WillRepeatedly(Return(true));

    initialExpectations +=
        EXPECT_CALL(yAxisControllerMock_, isAtHomePosition())
            .WillOnce(Return(false))
            .WillOnce(Return(false))
            .WillRepeatedly(Return(true));

    initialExpectations +=
        EXPECT_CALL(zAxisControllerMock_, isAtHomePosition())
            .WillOnce(Return(false))
            .WillOnce(Return(false))
            .WillOnce(Return(false))
            .WillRepeatedly(Return(true));

    EXPECT_CALL(xAxisControllerMock_, moveToStartPosition())
        .After(initialExpectations);
    EXPECT_CALL(yAxisControllerMock_, moveToStartPosition())
        .After(initialExpectations);
    EXPECT_CALL(zAxisControllerMock_, moveToStartPosition())
        .After(initialExpectations);

    calibrationTask_.start();

    for (uint8_t i = 0; i < TICK_AMOUNT; i++) {
        calibrationTask_.tick();
    }
}

TEST_F(
    CalibrationTaskTest,
    GIVEN_calibrationTask_WHEN_axesAreAtStartPosition_THEN_taskIsFinished
) {
    EXPECT_CALL(xAxisControllerMock_, isAtHomePosition())
        .WillOnce(Return(true));
    EXPECT_CALL(xAxisControllerMock_, isAtStartPosition())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(yAxisControllerMock_, isAtHomePosition())
        .WillOnce(Return(true));
    EXPECT_CALL(yAxisControllerMock_, isAtStartPosition())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(zAxisControllerMock_, isAtHomePosition())
        .WillOnce(Return(true));
    EXPECT_CALL(zAxisControllerMock_, isAtStartPosition())
        .WillRepeatedly(Return(true));

    calibrationTask_.start();

    ASSERT_FALSE(calibrationTask_.isFinished());

    for (uint8_t i = 0; i < TICK_AMOUNT; i++) {
        calibrationTask_.tick();
    }

    ASSERT_TRUE(calibrationTask_.isFinished());
}

TEST_F(
    CalibrationTaskTest,
    GIVEN_calibrationTask_WHEN_taskIsReset_THEN_movementIsCanceled
) {
    calibrationTask_.start();

    EXPECT_CALL(xAxisControllerMock_, cancelMovement());
    EXPECT_CALL(yAxisControllerMock_, cancelMovement());
    EXPECT_CALL(zAxisControllerMock_, cancelMovement());

    calibrationTask_.reset();
}

TEST_F(
    CalibrationTaskTest,
    GIVEN_calibrationTask_WHEN_taskIsReset_THEN_resultsAreReset
) {
    calibrationTask_.start();

    calibrationTask_.reset();

    const bool success = calibrationTask_.consumeResult();
    ASSERT_FALSE(success);
}

TEST_F(
    CalibrationTaskTest,
    GIVEN_calibrationTask_WHEN_resultIsConsumed_THEN_resultsAreReset
) {
    EXPECT_CALL(xAxisControllerMock_, isAtHomePosition())
        .WillOnce(Return(true));
    EXPECT_CALL(xAxisControllerMock_, isAtStartPosition())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(yAxisControllerMock_, isAtHomePosition())
        .WillOnce(Return(true));
    EXPECT_CALL(yAxisControllerMock_, isAtStartPosition())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(zAxisControllerMock_, isAtHomePosition())
        .WillOnce(Return(true));
    EXPECT_CALL(zAxisControllerMock_, isAtStartPosition())
        .WillRepeatedly(Return(true));

    calibrationTask_.start();

    for (uint8_t i = 0; i < TICK_AMOUNT; i++) {
        calibrationTask_.tick();
    }

    const bool successResults = calibrationTask_.consumeResult();
    const bool cleanedResults = calibrationTask_.consumeResult();

    ASSERT_TRUE(successResults);
    ASSERT_FALSE(cleanedResults);
}
}