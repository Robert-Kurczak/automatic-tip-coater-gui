#pragma once

#include "application/System/Tasks/Task/ITask.hpp"

#include "gmock/gmock.h"

using namespace testing;

namespace ATC {
class TaskMock : public ITask {
public:
    MOCK_METHOD(void, start, (), (override));
    MOCK_METHOD(void, reset, (), (override));
    MOCK_METHOD(void, tick, (), (override));
    MOCK_METHOD(bool, isFinished, (), (const override));
};
}