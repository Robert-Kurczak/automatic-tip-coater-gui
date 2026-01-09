#pragma once

#include "../ITaskScheduler.hpp"

namespace ATC {
class SingleTaskScheduler : public ITaskScheduler {
private:
    ITask& nullTask_;
    ITask* currentTask_;

public:
    SingleTaskScheduler(ITask& nullTask);

    void schedule(ITask& task) override;
    void tick() override;
    void cancelAll() override;
};
}