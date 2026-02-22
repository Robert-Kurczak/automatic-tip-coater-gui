#pragma once

#include "application/System/Tasks/Task/IConsumableTask.hpp"

#include "gmock/gmock.h"

using namespace testing;

namespace ATC {
template<typename TaskResult>
class ConsumableTaskMock : public IConsumableTask<TaskResult> {
public:
    MOCK_METHOD(void, start, (), (override));

    MOCK_METHOD(void, reset, (), (override));

    MOCK_METHOD(void, tick, (), (override));

    MOCK_METHOD(bool, isFinished, (), (const override));

    MOCK_METHOD(TaskResult, consumeResult, (), (override));
};
}