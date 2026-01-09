#pragma once

#include "../Task/ITask.hpp"

namespace ATC {
class ITaskScheduler {
public:
    ITaskScheduler() = default;
    ITaskScheduler(const ITaskScheduler&) = delete;
    ITaskScheduler& operator=(const ITaskScheduler&) = delete;
    ITaskScheduler(ITaskScheduler&&) = delete;
    ITaskScheduler& operator=(ITaskScheduler&&) = delete;
    virtual ~ITaskScheduler() = default;

    virtual void schedule(ITask& task) = 0;
    virtual void tick() = 0;
    virtual void cancelAll() = 0;
};
}