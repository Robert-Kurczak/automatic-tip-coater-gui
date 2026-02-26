#include "application/System/Tasks/TaskScheduler/SingleTaskScheduler/SingleTaskScheduler.hpp"

#include "platform/gtest/Mocks/Tasks/TaskMock.hpp"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

using namespace testing;

namespace ATC {
class SingleTaskSchedulerTest : public Test {
public:
    static constexpr uint8_t TICK_AMOUNT = 10;

    TaskMock nullTask_ {};

    SingleTaskScheduler singleTaskScheduler_ {nullTask_};
};

TEST_F(
    SingleTaskSchedulerTest,
    GIVEN_singleTaskScheduler_WHEN_nothingIsScheduled_THEN_nullTaskIsTicked
) {
    EXPECT_CALL(nullTask_, tick()).Times(TICK_AMOUNT);

    for (uint8_t i = 0; i < TICK_AMOUNT; i++) {
        singleTaskScheduler_.tick();
    }
}

TEST_F(
    SingleTaskSchedulerTest,
    GIVEN_singleTaskScheduler_WHEN_newTaskIsScheduled_THEN_previousTaskIsReset
) {
    TaskMock previousTaskMock_ {};
    TaskMock newTaskMock_ {};

    singleTaskScheduler_.schedule(previousTaskMock_);

    EXPECT_CALL(previousTaskMock_, reset());

    singleTaskScheduler_.schedule(newTaskMock_);
}

TEST_F(
    SingleTaskSchedulerTest,
    GIVEN_singleTaskScheduler_WHEN_newTaskIsScheduled_THEN_newTaskIsStarted
) {
    TaskMock newTaskMock_ {};

    EXPECT_CALL(newTaskMock_, start());

    singleTaskScheduler_.schedule(newTaskMock_);
}

TEST_F(
    SingleTaskSchedulerTest,
    GIVEN_singleTaskScheduler_WHEN_newTaskIsScheduled_THEN_newTaskIsTicked
) {
    TaskMock newTaskMock_ {};

    singleTaskScheduler_.schedule(newTaskMock_);

    EXPECT_CALL(newTaskMock_, tick()).Times(TICK_AMOUNT);

    for (uint8_t i = 0; i < TICK_AMOUNT; i++) {
        singleTaskScheduler_.tick();
    }
}

TEST_F(
    SingleTaskSchedulerTest,
    GIVEN_singleTaskScheduler_WHEN_currentTaskFinishes_THEN_taskIsReset
) {
    TaskMock newTaskMock_ {};

    singleTaskScheduler_.schedule(newTaskMock_);

    {
        InSequence sequence;

        EXPECT_CALL(newTaskMock_, isFinished())
            .WillRepeatedly(Return(true));
        EXPECT_CALL(newTaskMock_, reset());
    }

    for (uint8_t i = 0; i < TICK_AMOUNT; i++) {
        singleTaskScheduler_.tick();
    }
}

TEST_F(
    SingleTaskSchedulerTest,
    GIVEN_singleTaskScheduler_WHEN_currentTaskFinishes_THEN_nullTaskIsTicked
) {
    TaskMock newTaskMock_ {};

    singleTaskScheduler_.schedule(newTaskMock_);

    EXPECT_CALL(newTaskMock_, isFinished()).WillRepeatedly(Return(true));
    EXPECT_CALL(nullTask_, tick()).Times(AtLeast(TICK_AMOUNT - 2));

    for (uint8_t i = 0; i < TICK_AMOUNT; i++) {
        singleTaskScheduler_.tick();
    }
}

TEST_F(
    SingleTaskSchedulerTest,
    GIVEN_singleTaskScheduler_WHEN_currentTaskIsCanceled_THEN_taskIsReset
) {
    TaskMock newTaskMock_ {};

    singleTaskScheduler_.schedule(newTaskMock_);

    EXPECT_CALL(newTaskMock_, reset());

    singleTaskScheduler_.cancelAll();

}

TEST_F(
    SingleTaskSchedulerTest,
    GIVEN_singleTaskScheduler_WHEN_currentTaskIsCanceled_THEN_nullTaskIsTicked
) {
    TaskMock newTaskMock_ {};

    singleTaskScheduler_.schedule(newTaskMock_);
    singleTaskScheduler_.cancelAll();

    EXPECT_CALL(nullTask_, tick()).Times(AtLeast(TICK_AMOUNT - 2));

    for (uint8_t i = 0; i < TICK_AMOUNT; i++) {
        singleTaskScheduler_.tick();
    }
}
}