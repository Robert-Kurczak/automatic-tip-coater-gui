#include "CoatingTask.hpp"

#include <functional>

namespace ATC {
void CoatingTask::calibrateAxes() {
    calibrationTask_.start();
    currentStage_++;
}

void CoatingTask::waitForCalibrationFinish() {
    calibrationTask_.tick();

    if (calibrationTask_.isFinished()) {
        const bool wasCalibrationSuccessful =
            calibrationTask_.consumeResult();

        if (wasCalibrationSuccessful) {
            currentStage_++;
        } else {
            state_ = TaskState::FINISHED;
        }
    }
}

void CoatingTask::startHeater() {
    heaterController_.turnOn();
    currentStage_++;
}

void CoatingTask::moveAxesToInitialPosition() {
    xAxisController_.moveToHeaterFrontPosition();
    yAxisController_.moveToStartPosition();
    zAxisController_.moveToStartPosition();
    currentStage_++;
}

void CoatingTask::waitForAxesAtInitialPosition() {
    const bool isXAxisAtPosition =
        xAxisController_.isAtHeaterFrontPosition();
    const bool isYAxisAtPosition = yAxisController_.isAtStartPosition();
    const bool isZAxisAtPosition = zAxisController_.isAtStartPosition();

    const bool axesAtPosition =
        isXAxisAtPosition && isYAxisAtPosition && isZAxisAtPosition;

    if (axesAtPosition) {
        currentStage_++;
    }
}

void CoatingTask::moveZAxisToEndPosition() {
    zAxisController_.moveToEndPosition();
    currentStage_++;
}

void CoatingTask::waitForZAxisAtEndPosition() {
    if (zAxisController_.isAtEndPosition()) {
        currentStage_++;
    }
}

void CoatingTask::detectTipWithYAxis() {
    yAxisController_.moveToDetectTip();
    currentStage_++;
}

void CoatingTask::waitForTipDetection() {
    if (yAxisController_.isTipDetected()) {
        currentStage_++;
    }
}

void CoatingTask::moveYAxisToCoatingPosition() {
    yAxisController_.moveToCoatingPosition();
    currentStage_++;
}

void CoatingTask::waitForYAxisAtCoatingPosition() {
    if (yAxisController_.isAtCoatingPosition()) {
        currentStage_++;
    }
}

void CoatingTask::moveZAxisToStartPosition() {
    zAxisController_.moveToStartPosition();
    currentStage_++;
}

void CoatingTask::waitForZAxisAtStartPosition() {
    if (zAxisController_.isAtStartPosition()) {
        currentStage_++;
    }
}

void CoatingTask::moveXAxisToEndPosition() {
    xAxisController_.moveToEndPosition();
    currentStage_++;
}

void CoatingTask::waitForXAxisAtEndPosition() {
    if (zAxisController_.isAtEndPosition()) {
        currentStage_++;
    }
}

void CoatingTask::waitForHeaterTemperature() {
    if (heaterController_.isAtTargetTemperature()) {
        currentStage_++;
    }
}

void CoatingTask::startRotation() {
    spindleController_.startRotation();
    currentStage_++;
}

void CoatingTask::moveXAxisToHeaterFrontPosition() {
    xAxisController_.moveToHeaterFrontPosition();
    currentStage_++;
}

void CoatingTask::waitForXAxisAtHeaterFrontPosition() {
    if (xAxisController_.isAtHeaterFrontPosition()) {
        currentStage_++;
    }
}

void CoatingTask::startTimedRotationInHeaterFront() {
    spindleController_.startRotation();
    currentStage_++;
}

void CoatingTask::waitForTimedRotationToFinish() {
    if (spindleController_.isTimedRotationFinished()) {
        currentStage_++;
    }
}

void CoatingTask::moveXAxisToStartPosition() {
    xAxisController_.moveToStartPosition();
    currentStage_++;
}

void CoatingTask::waitForXAxisAtStartPosition() {
    if (xAxisController_.isAtStartPosition()) {
        currentStage_++;
    }
}

void CoatingTask::stopHeater() {
    heaterController_.turnOff();
    currentStage_++;
}

void CoatingTask::stopRotation() {
    spindleController_.stopRotation();
    currentStage_++;
}

void CoatingTask::finishTask() {
    state_ = TaskState::FINISHED;
    wasSuccessful_ = true;
}

const std::array<CoatingTask::stageMethod, 30> CoatingTask::stages_ {
    &CoatingTask::calibrateAxes,
    &CoatingTask::waitForCalibrationFinish,

    &CoatingTask::startHeater,

    &CoatingTask::moveAxesToInitialPosition,
    &CoatingTask::waitForAxesAtInitialPosition,

    &CoatingTask::moveZAxisToEndPosition,
    &CoatingTask::waitForZAxisAtEndPosition,

    &CoatingTask::detectTipWithYAxis,
    &CoatingTask::waitForTipDetection,

    &CoatingTask::moveYAxisToCoatingPosition,
    &CoatingTask::waitForYAxisAtCoatingPosition,

    &CoatingTask::moveZAxisToStartPosition,
    &CoatingTask::waitForZAxisAtStartPosition,

    &CoatingTask::moveXAxisToEndPosition,
    &CoatingTask::waitForXAxisAtEndPosition,

    &CoatingTask::waitForHeaterTemperature,

    &CoatingTask::startRotation,

    &CoatingTask::moveZAxisToEndPosition,
    &CoatingTask::waitForZAxisAtEndPosition,

    &CoatingTask::moveXAxisToHeaterFrontPosition,
    &CoatingTask::waitForXAxisAtHeaterFrontPosition,

    &CoatingTask::startTimedRotationInHeaterFront,
    &CoatingTask::waitForTimedRotationToFinish,

    &CoatingTask::moveXAxisToStartPosition,
    &CoatingTask::waitForXAxisAtStartPosition,

    &CoatingTask::stopRotation,

    &CoatingTask::stopHeater,

    &CoatingTask::moveZAxisToStartPosition,
    &CoatingTask::waitForZAxisAtEndPosition,

    &CoatingTask::finishTask
};

CoatingTask::CoatingTask(
    IConsumableTask<bool>& calibrationTask,
    IXAxisController& xAxisController,
    IYAxisController& yAxisController,
    IZAxisController& zAxisController,
    ISpindleController& spindleController,
    IHeaterController& heaterController
) :
    calibrationTask_(calibrationTask),
    xAxisController_(xAxisController),
    yAxisController_(yAxisController),
    zAxisController_(zAxisController),
    spindleController_(spindleController),
    heaterController_(heaterController) {}

void CoatingTask::start() {
    state_ = TaskState::RUNNING;
};

void CoatingTask::reset() {
    xAxisController_.cancelMovement();
    yAxisController_.cancelMovement();
    zAxisController_.cancelMovement();

    state_ = TaskState::IDLE;
    currentStage_ = 0;
    wasSuccessful_ = false;
}

void CoatingTask::tick() {
    if (state_ != TaskState::RUNNING) {
        return;
    }

    std::invoke(stages_.at(currentStage_), this);
};

bool CoatingTask::isFinished() const {
    return state_ == TaskState::FINISHED;
}

bool CoatingTask::consumeResult() {
    if (state_ != TaskState::FINISHED) {
        return false;
    }

    const bool result = wasSuccessful_;
    reset();

    return result;
}
}