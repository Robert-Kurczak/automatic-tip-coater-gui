#include "CoatingTask.hpp"

#include <functional>

namespace ATC {
void CoatingTask::resetStates() {
    state_ = TaskState::IDLE;
    currentStage_ = 0;
    wasSuccessful_ = false;
}

void CoatingTask::moveAxesToInitialPosition() {
    devices_.xAxisController.moveToHeaterFrontPosition();
    devices_.yAxisController.moveToStartPosition();
    devices_.zAxisController.moveToStartPosition();
    currentStage_++;
}

void CoatingTask::waitForAxesAtInitialPosition() {
    const bool xAxisAtPosition =
        devices_.xAxisController.isAtHeaterFrontPosition();
    const bool yAxisAtPosition =
        devices_.yAxisController.isAtStartPosition();
    const bool zAxisAtPosition =
        devices_.zAxisController.isAtStartPosition();

    const bool axesAtPosition =
        xAxisAtPosition && yAxisAtPosition && zAxisAtPosition;

    if (axesAtPosition) {
        currentStage_++;
    }
}

void CoatingTask::moveZAxisToEndPosition() {
    devices_.zAxisController.moveToEndPosition();
    currentStage_++;
}

void CoatingTask::waitForZAxisAtEndPosition() {
    if (devices_.zAxisController.isAtEndPosition()) {
        currentStage_++;
    }
}

void CoatingTask::detectTipWithYAxis() {
    devices_.yAxisController.moveToDetectTip();
    currentStage_++;
}

void CoatingTask::waitForTipDetection() {
    if (devices_.yAxisController.isTipDetected()) {
        currentStage_++;
    }
}

void CoatingTask::moveYAxisToCoatingPosition() {
    devices_.yAxisController.moveToCoatingPosition();
    currentStage_++;
}

void CoatingTask::waitForYAxisAtCoatingPosition() {
    if (devices_.yAxisController.isAtCoatingPosition()) {
        currentStage_++;
    }
}

void CoatingTask::moveZAxisToStartPosition() {
    devices_.zAxisController.moveToStartPosition();
    currentStage_++;
}

void CoatingTask::waitForZAxisAtStartPosition() {
    if (devices_.zAxisController.isAtStartPosition()) {
        currentStage_++;
    }
}

void CoatingTask::moveXAxisToEndPosition() {
    devices_.xAxisController.moveToEndPosition();
    currentStage_++;
}

void CoatingTask::waitForXAxisAtEndPosition() {
    if (devices_.zAxisController.isAtEndPosition()) {
        currentStage_++;
    }
}

void CoatingTask::startRotation() {
    devices_.rotator.startRotation();
    currentStage_++;
}

void CoatingTask::moveXAxisToHeaterFrontPosition() {
    devices_.xAxisController.moveToHeaterFrontPosition();
    currentStage_++;
}

void CoatingTask::waitForXAxisAtHeaterFrontPosition() {
    if (devices_.xAxisController.isAtHeaterFrontPosition()) {
        currentStage_++;
    }
}

void CoatingTask::startTimedRotationInHeaterFront() {
    devices_.rotator.startTimedRotation();
    currentStage_++;
}

void CoatingTask::waitForTimedRotationToFinish() {
    if (devices_.rotator.timedRotationFinished()) {
        currentStage_++;
    }
}

void CoatingTask::moveXAxisToStartPosition() {
    devices_.xAxisController.moveToStartPosition();
    currentStage_++;
}

void CoatingTask::waitForXAxisAtStartPosition() {
    if (devices_.xAxisController.isAtStartPosition()) {
        currentStage_++;
    }
}

void CoatingTask::stopRotation() {
    devices_.rotator.stopRotation();
    currentStage_++;
}

void CoatingTask::finishTask() {
    state_ = TaskState::FINISHED;
    wasSuccessful_ = true;
}

CoatingTask::CoatingTask(BoardDevices& devices) : devices_(devices) {}

void CoatingTask::start() {
    state_ = TaskState::RUNNING;
};

void CoatingTask::tick() {
    if (state_ != TaskState::RUNNING) {
        return;
    }

    std::invoke(stages_[currentStage_], this);
};

bool CoatingTask::isFinished() const {
    return state_ == TaskState::FINISHED;
}

bool CoatingTask::consumeResult() {
    if (state_ != TaskState::FINISHED) {
        return false;
    }

    const bool result = wasSuccessful_;
    resetStates();

    return result;
}
}