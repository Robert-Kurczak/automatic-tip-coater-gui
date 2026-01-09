#pragma once

#include "IConsumableTaskService.hpp"
#include "application/System/Tasks/Task/IConsumableTask.hpp"
#include "application/System/Tasks/TaskScheduler/ITaskScheduler.hpp"

namespace ATC {
template<typename TaskResult>
class ConsumableTaskService : public IConsumableTaskService<TaskResult> {
private:
    ITaskScheduler& scheduler_;
    IConsumableTask<TaskResult>& task_;

public:
    ConsumableTaskService(const ConsumableTaskService&) = delete;
    ConsumableTaskService& operator=(const ConsumableTaskService&) =
        delete;
    ConsumableTaskService(ConsumableTaskService&&) = delete;
    ConsumableTaskService& operator=(ConsumableTaskService&&) = delete;
    virtual ~ConsumableTaskService() = default;

    ConsumableTaskService(
        ITaskScheduler& scheduler,
        IConsumableTask<TaskResult>& task
    ) :
        scheduler_(scheduler),
        task_(task) {}

    void schedule() override {
        scheduler_.schedule(task_);
    }

    [[nodiscard]] bool isFinished() const override {
        return task_.isFinished();
    }

    TaskResult consumeResult() override {
        return task_.consumeResult();
    }
};
}
