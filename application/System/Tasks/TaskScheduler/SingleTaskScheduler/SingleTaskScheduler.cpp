#include "SingleTaskScheduler.hpp"

namespace ATC {
SingleTaskScheduler::SingleTaskScheduler(ITask& nullTask) :
    nullTask_(nullTask),
    currentTask_(&nullTask_) {}

void SingleTaskScheduler::schedule(ITask& task) {
    currentTask_->reset();

    currentTask_ = &task;
    currentTask_->start();
}

void SingleTaskScheduler::tick() {
    if (currentTask_->isFinished()) {
        currentTask_->reset();
        currentTask_ = &nullTask_;
    } else {
        currentTask_->tick();
    }
}

void SingleTaskScheduler::cancelAll() {
    currentTask_->reset();
    currentTask_ = &nullTask_;
}
}