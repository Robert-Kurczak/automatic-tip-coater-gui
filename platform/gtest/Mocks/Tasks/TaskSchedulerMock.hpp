#pragma once

#include "application/System/Tasks/Task/ITask.hpp"
#include "application/System/Tasks/TaskScheduler/ITaskScheduler.hpp"

#include "gmock/gmock.h"

namespace ATC {
class TaskSchedulerMock : public ITaskScheduler {
public:
    MOCK_METHOD(void, schedule, (ITask&), (override));

    MOCK_METHOD(void, tick, (), (override));

    MOCK_METHOD(void, cancelAll, (), (override));
};
}