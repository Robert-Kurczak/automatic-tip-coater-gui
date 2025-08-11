#include "CoatingTask.hpp"

#include <functional>

namespace ATC {
void CoatingTask::resetStates() {
    state_ = TaskState::IDLE;
    currentStage_ = 0;
    wasSuccessful_ = false;
}

void CoatingTask::moveAxesToInitialPosition() {
    const bool xAxisAtPosition = devices_.xAxis.isAtHeaterFrontPosition();
    if (!xAxisAtPosition) {
        devices_.xAxis.moveTowardsHeaterFrontPosition();
    }

    const bool yAxisAtPosition = devices_.xAxis.isAtHeaterFrontPosition();
    if (!yAxisAtPosition) {
        devices_.yAxis.moveTowardsStartPosition();
    }

    const bool zAxisAtPosition = devices_.xAxis.isAtHeaterFrontPosition();
    if (!zAxisAtPosition) {
        devices_.zAxis.moveTowardsStartPosition();
    }

    const bool axesAtPosition =
        xAxisAtPosition && yAxisAtPosition && zAxisAtPosition;

    if (axesAtPosition) {
        currentStage_++;
    }
}

void CoatingTask::moveZAxisToEndPosition() {
    devices_.zAxis.moveTowardsEndPosition();

    if (devices_.zAxis.isAtEndPosition()) {
        currentStage_++;
    }
}

void CoatingTask::detectTipWithYAxis() {
    devices_.yAxis.detectTip();

    if (devices_.yAxis.tipDetected()) {
        currentStage_++;
    }
}

void CoatingTask::moveYAxisToCoatingPosition() {
    devices_.yAxis.moveTowardsCoatingPosition();

    if (devices_.yAxis.isAtCoatingPosition()) {
        currentStage_++;
    }
}

void CoatingTask::moveZAxisToStartPosition() {
    devices_.zAxis.moveTowardsStartPosition();

    if (devices_.zAxis.isAtStartPosition()) {
        currentStage_++;
    }
}

void CoatingTask::moveXAxisToEndPosition() {
    devices_.xAxis.moveTowardsEndPosition();

    if (devices_.zAxis.isAtEndPosition()) {
        currentStage_++;
    }
}

void CoatingTask::startRotation() {
    devices_.rotator.startRotation();
    currentStage_++;
}

void CoatingTask::moveXAxisToHeaterFront() {
    devices_.xAxis.moveTowardsHeaterFrontPosition();

    if (devices_.xAxis.isAtHeaterFrontPosition()) {
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
    devices_.xAxis.moveTowardsStartPosition();

    if (devices_.xAxis.isAtStartPosition()) {
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