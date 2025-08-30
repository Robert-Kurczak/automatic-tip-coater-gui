#pragma once

namespace ATC {
template<typename TaskResult>
class IConsumableTaskService {
public:
    virtual ~IConsumableTaskService() = default;

    virtual void schedule() = 0;
    virtual bool isFinished() const = 0;
    virtual TaskResult consumeResult() = 0;
};
}