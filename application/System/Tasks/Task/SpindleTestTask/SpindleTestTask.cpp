#include "SpindleTestTask.hpp"

#include <functional>

namespace ATC {
void SpindleTestTask::startSpindle() {
    spindleController_.startTimedRotation(rotationDurationInMillis_);

    currentStage_++;
}

void SpindleTestTask::waitForRotationToFinish() {
    const bool isRotationFinished =
        spindleController_.isTimedRotationFinished();

    if (isRotationFinished) {
        currentStage_++;
    }
}

void SpindleTestTask::finishTask() {
    testResults_.motorDriverSuccess =
        !spindleController_.wasFaultReported();

    state_ = TaskState::FINISHED;
}

SpindleTestTask::SpindleTestTask(
    ISpindleController& spindleController,
    uint32_t rotationDurationInMillis
) :
    spindleController_(spindleController),
    rotationDurationInMillis_(rotationDurationInMillis) {}

void SpindleTestTask::start() {
    state_ = TaskState::RUNNING;
}

void SpindleTestTask::reset() {
    state_ = TaskState::IDLE;
    currentStage_ = 0;

    testResults_.motorDriverSuccess = false;
}

void SpindleTestTask::tick() {
    if (state_ != TaskState::RUNNING) {
        return;
    }

    std::invoke(stages_[currentStage_], this);
}

bool SpindleTestTask::isFinished() const {
    return state_ == TaskState::FINISHED;
}

SpindleTestResults SpindleTestTask::consumeResult() {
    if (state_ != TaskState::FINISHED) {
        return SpindleTestResults {.motorDriverSuccess = false};
    }

    const SpindleTestResults result = testResults_;
    reset();

    return result;
}

}
