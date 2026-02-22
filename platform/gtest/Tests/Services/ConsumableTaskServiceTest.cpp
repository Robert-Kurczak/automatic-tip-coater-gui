#include "application/System/Services/ConsumableTaskService/ConsumableTaskService.hpp"

#include "platform/gtest/Mocks/Tasks/ConsumableTaskMock.hpp"
#include "platform/gtest/Mocks/Tasks/TaskSchedulerMock.hpp"

#include "gtest/gtest.h"

using namespace testing;

namespace ATC {
class ConsumableTaskServiceTest : public Test {
public:
    TaskSchedulerMock taskSchedulerMock_ {};
    ConsumableTaskMock<uint32_t> consumableTaskMock_ {};

    ConsumableTaskService<uint32_t> consumableTaskService_ {
        taskSchedulerMock_,
        consumableTaskMock_
    };
};

TEST_F(
    ConsumableTaskServiceTest,
    GIVEN_consumableTaskService_WHEN_scheduleIsCalled_THEN_callIsForwardedToScheduler
) {
    EXPECT_CALL(taskSchedulerMock_, schedule(Ref(consumableTaskMock_)));

    consumableTaskService_.schedule();
}

TEST_F(
    ConsumableTaskServiceTest,
    GIVEN_consumableTaskService_WHEN_isFinishedIsCalled_THEN_callIsForwardedToTask
) {
    EXPECT_CALL(consumableTaskMock_, isFinished())
        .WillOnce(Return(false));

    ASSERT_FALSE(consumableTaskService_.isFinished());

    EXPECT_CALL(consumableTaskMock_, isFinished()).WillOnce(Return(true));

    ASSERT_TRUE(consumableTaskService_.isFinished());
}

TEST_F(
    ConsumableTaskServiceTest,
    GIVEN_consumableTaskService_WHEN_consumeResultIsCalled_THEN_callIsForwardedToTask
) {
    constexpr uint32_t result1 = 0xDEADBEEF;
    constexpr uint32_t result2 = 0xAABBCCDD;

    EXPECT_CALL(consumableTaskMock_, consumeResult())
        .WillOnce(Return(result1))
        .WillOnce(Return(result2));

    ASSERT_EQ(consumableTaskService_.consumeResult(), result1);
    ASSERT_EQ(consumableTaskService_.consumeResult(), result2);
}
}