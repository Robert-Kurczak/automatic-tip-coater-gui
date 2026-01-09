#pragma once

namespace ATC {
template<typename TaskResult>
class IConsumableTaskService {
public:
    IConsumableTaskService() = default;
    IConsumableTaskService(const IConsumableTaskService&) = delete;
    IConsumableTaskService& operator=(const IConsumableTaskService&) =
        delete;
    IConsumableTaskService(IConsumableTaskService&&) = delete;
    IConsumableTaskService& operator=(IConsumableTaskService&&) = delete;
    virtual ~IConsumableTaskService() = default;

    virtual void schedule() = 0;
    [[nodiscard]] virtual bool isFinished() const = 0;
    virtual TaskResult consumeResult() = 0;
};
}