#include "SingleTaskScheduler.hpp"

namespace ATC {
// TODO replace nullptr with Null Object?
void SingleTaskScheduler::schedule(ITask& task) {
    if (currentTask_) {
        currentTask_->reset();
    }

    currentTask_ = &task;
    currentTask_->start();
}

void SingleTaskScheduler::tick() {
    if (currentTask_ && currentTask_->isFinished()) {
        currentTask_->reset();
        currentTask_ = nullptr;
    } else if (currentTask_) {
        currentTask_->tick();
    }
}

void SingleTaskScheduler::cancelAll() {
    if (currentTask_) {
        currentTask_->reset();
    }

    currentTask_ = nullptr;
}
}