#pragma once

#include <cstdint>

namespace ATC {
class ITask {
public:
    enum class TaskState : uint8_t { IDLE, RUNNING, FINISHED };

    ITask() = default;
    ITask(const ITask&) = delete;
    ITask& operator=(const ITask&) = delete;
    ITask(ITask&&) = delete;
    ITask& operator=(ITask&&) = delete;
    virtual ~ITask() = default;

    virtual void start() = 0;
    virtual void reset() = 0;
    virtual void tick() = 0;
    [[nodiscard]] virtual bool isFinished() const = 0;
};
}