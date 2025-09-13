#include "CalibrationTask.hpp"

namespace ATC {
void CalibrationTask::moveAxesToHomePosition() {
    xAxisController_.moveToHomePosition();
    yAxisController_.moveToHomePosition();
    zAxisController_.moveToHomePosition();

    currentStage_++;
}

void CalibrationTask::waitForAxesAtHomePosition() {
    const bool isXAxisAtPosition = xAxisController_.isAtHomePosition();
    const bool isYAxisAtPosition = yAxisController_.isAtHomePosition();
    const bool isZAxisAtPosition = zAxisController_.isAtHomePosition();

    const bool axesAtPosition =
        isXAxisAtPosition && isYAxisAtPosition && isZAxisAtPosition;

    if (axesAtPosition) {
        currentStage_++;
    }
}

void CalibrationTask::moveAxesToStartPosition() {
    xAxisController_.moveToStartPosition();
    yAxisController_.moveToStartPosition();
    zAxisController_.moveToStartPosition();

    currentStage_++;
}

void CalibrationTask::waitForAxesAtStartPosition() {
    const bool isXAxisAtPosition = xAxisController_.isAtStartPosition();
    const bool isYAxisAtPosition = yAxisController_.isAtStartPosition();
    const bool isZAxisAtPosition = zAxisController_.isAtStartPosition();

    const bool axesAtPosition =
        isXAxisAtPosition && isYAxisAtPosition && isZAxisAtPosition;

    if (axesAtPosition) {
        currentStage_++;
    }
}

void CalibrationTask::finishTask() {
    state_ = TaskState::FINISHED;
    wasSuccessful_ = true;
}

CalibrationTask::CalibrationTask(
    IXAxisController& xAxisController,
    IYAxisController& yAxisController,
    IZAxisController& zAxisController
) :
    xAxisController_(xAxisController),
    yAxisController_(yAxisController),
    zAxisController_(zAxisController) {}

void CalibrationTask::start() {
    state_ = TaskState::RUNNING;
}

void CalibrationTask::reset() {
    state_ = TaskState::IDLE;
    currentStage_ = 0;
    wasSuccessful_ = false;
}

void CalibrationTask::tick() {
    if (state_ != TaskState::RUNNING) {
        return;
    }

    std::invoke(stages_[currentStage_], this);
}

bool CalibrationTask::isFinished() const {
    return state_ == TaskState::FINISHED;
}

bool CalibrationTask::consumeResult() {
    if (state_ != TaskState::FINISHED) {
        return false;
    }

    const bool result = wasSuccessful_;
    reset();

    return result;
}
}