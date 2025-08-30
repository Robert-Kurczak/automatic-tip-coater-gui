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
    ConsumableTaskService(
        ITaskScheduler& scheduler,
        IConsumableTask<TaskResult>& task
    ) :
        scheduler_(scheduler),
        task_(task) {}

    virtual void schedule() override {
        scheduler_.schedule(task_);
    }

    virtual bool isFinished() const override {
        return task_.isFinished();
    }

    virtual TaskResult consumeResult() override {
        return task_.consumeResult();
    }
};
}
