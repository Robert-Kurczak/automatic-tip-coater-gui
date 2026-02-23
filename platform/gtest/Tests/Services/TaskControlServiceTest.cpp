#pragma once

#include "application/System/Services/TaskControlService/TaskControlService.hpp"

#include "platform/gtest/Mocks/Tasks/TaskSchedulerMock.hpp"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

using namespace testing;

namespace ATC {
class TaskControlServiceTest : public Test {
public:
    TaskSchedulerMock taskSchedulerMock_ {};

    TaskControlService taskControlService_ {taskSchedulerMock_};
};

TEST_F(
    TaskControlServiceTest,
    GIVEN_taskControlService_WHEN_cancelAllIsCalled_THEN_callIsForwardedToScheduler
) {
    EXPECT_CALL(taskSchedulerMock_, cancelAll());

    taskControlService_.cancelAll();
}
}