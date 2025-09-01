#pragma once

#include "../ITaskScheduler.hpp"

namespace ATC {
class SingleTaskScheduler : public ITaskScheduler {
private:
    ITask& nullTask_;
    ITask* currentTask_;

public:
    SingleTaskScheduler(ITask& nullTask);

    virtual void schedule(ITask& task) override;
    virtual void tick() override;
    virtual void cancelAll() override;
};
}