#pragma once

#include "../ITaskScheduler.hpp"

namespace ATC {
class SingleTaskScheduler : public ITaskScheduler {
private:
    ITask* currentTask_ = nullptr;

public:
    virtual void schedule(ITask& task) override;
    virtual void tick() override;
    virtual void cancelAll() override;
};
}