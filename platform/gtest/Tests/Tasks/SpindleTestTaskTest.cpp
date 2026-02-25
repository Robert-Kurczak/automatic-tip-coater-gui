#include "application/System/Tasks/Task/SpindleTestTask/SpindleTestTask.hpp"

#include "application/System/Tasks/Task/SpindleTestTask/SpindleTestResults.hpp"
#include "platform/gtest/Mocks/Controllers/SpindleControllerMock.hpp"

#include "gtest/gtest.h"

using namespace testing;

namespace ATC {
class SpindleTestTaskTest : public Test {
public:
    static constexpr uint8_t TICK_AMOUNT = 50;

    static constexpr uint32_t ROTATION_DURATION = 5000;
    SpindleControllerMock spindleControllerMock_ {};

    SpindleTestTask spindleTestTask_ {
        spindleControllerMock_,
        ROTATION_DURATION
    };
};

TEST_F(
    SpindleTestTaskTest,
    GIVEN_spindleTestTask_WHEN_taskIsNotStarted_THEN_taskIdlesWhenTicked
) {
    EXPECT_CALL(spindleControllerMock_, startTimedRotation()).Times(0);

    for (uint8_t i = 0; i < TICK_AMOUNT; i++) {
        spindleTestTask_.tick();
    }
}

TEST_F(
    SpindleTestTaskTest,
    GIVEN_spindleTestTask_WHEN_taskIsStarted_THEN_timedRotationIsStarted
) {
    EXPECT_CALL(
        spindleControllerMock_, startTimedRotation(ROTATION_DURATION)
    );

    spindleTestTask_.start();

    for (uint8_t i = 0; i < TICK_AMOUNT; i++) {
        spindleTestTask_.tick();
    }
}

TEST_F(
    SpindleTestTaskTest,
    GIVEN_spindleTestTask_WHEN_timedRotationFinishes_THEN_taskIsFinished
) {
    EXPECT_CALL(spindleControllerMock_, isTimedRotationFinished())
        .WillOnce(Return(false))
        .WillOnce(Return(false))
        .WillRepeatedly(Return(true));

    spindleTestTask_.start();

    ASSERT_FALSE(spindleTestTask_.isFinished());

    for (uint8_t i = 0; i < TICK_AMOUNT; i++) {
        spindleTestTask_.tick();
    }

    ASSERT_TRUE(spindleTestTask_.isFinished());
}

TEST_F(
    SpindleTestTaskTest,
    GIVEN_spindleTestTask_WHEN_driverFaultIsReported_THEN_motorDriverFailureIsReported
) {
    EXPECT_CALL(spindleControllerMock_, isTimedRotationFinished())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(spindleControllerMock_, wasFaultReported())
        .WillRepeatedly(Return(true));

    spindleTestTask_.start();

    for (uint8_t i = 0; i < TICK_AMOUNT; i++) {
        spindleTestTask_.tick();
    }

    ASSERT_TRUE(spindleTestTask_.isFinished());
    const SpindleTestResults results = spindleTestTask_.consumeResult();

    ASSERT_FALSE(results.motorDriverSuccess);
}

TEST_F(
    SpindleTestTaskTest,
    GIVEN_spindleTestTask_WHEN_driverFaultIsNotReported_THEN_motorDriverSuccessIsReported
) {
    EXPECT_CALL(spindleControllerMock_, isTimedRotationFinished())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(spindleControllerMock_, wasFaultReported())
        .WillRepeatedly(Return(false));

    spindleTestTask_.start();

    for (uint8_t i = 0; i < TICK_AMOUNT; i++) {
        spindleTestTask_.tick();
    }

    ASSERT_TRUE(spindleTestTask_.isFinished());
    const SpindleTestResults results = spindleTestTask_.consumeResult();

    ASSERT_TRUE(results.motorDriverSuccess);
}

TEST_F(
    SpindleTestTaskTest,
    GIVEN_spindleTestTask_WHEN_resultIsConsumed_THEN_resultsAreReset
) {
    EXPECT_CALL(spindleControllerMock_, isTimedRotationFinished())
        .WillRepeatedly(Return(true));

    spindleTestTask_.start();

    for (uint8_t i = 0; i < TICK_AMOUNT; i++) {
        spindleTestTask_.tick();
    }

    ASSERT_TRUE(spindleTestTask_.isFinished());

    const SpindleTestResults successfulResults =
        spindleTestTask_.consumeResult();

    const SpindleTestResults cleanedResults =
        spindleTestTask_.consumeResult();

    ASSERT_FALSE(cleanedResults.motorDriverSuccess);
}
}