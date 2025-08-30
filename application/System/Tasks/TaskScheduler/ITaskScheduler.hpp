#pragma once

#include "../Task/ITask.hpp"

namespace ATC {
class ITaskScheduler {
public:
    virtual ~ITaskScheduler() = default;

    virtual void schedule(ITask& task) = 0;
    virtual void tick() = 0;
    virtual void cancelAll() = 0;
};
}