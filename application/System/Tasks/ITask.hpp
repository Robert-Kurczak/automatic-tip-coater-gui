#pragma once

namespace ATC {
template<typename TaskResult>
class ITask {
public:
    enum class TaskState { IDLE, RUNNING, FINISHED };

    virtual void start() = 0;
    virtual void tick() = 0;
    virtual bool isFinished() const = 0;
    virtual TaskResult consumeResult() = 0;
};
}