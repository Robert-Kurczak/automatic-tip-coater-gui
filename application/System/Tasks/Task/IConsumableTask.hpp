#pragma once

#include "ITask.hpp"

namespace ATC {
template<typename TaskResult>
class IConsumableTask : public ITask {
public:
    virtual TaskResult consumeResult() = 0;
};
}