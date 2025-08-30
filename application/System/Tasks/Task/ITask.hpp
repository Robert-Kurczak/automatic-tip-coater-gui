#pragma once

namespace ATC {
class ITask {
public:
    enum class TaskState { IDLE, RUNNING, FINISHED };

    virtual ~ITask() = default;

    virtual void start() = 0;
    virtual void reset() = 0;
    virtual void tick() = 0;
    virtual bool isFinished() const = 0;
};
}