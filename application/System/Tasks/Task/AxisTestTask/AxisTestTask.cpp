#include "AxisTestTask.hpp"

#include <functional>

namespace ATC {
void AxisTestTask::calibrateAxes() {
    calibrationTask_.start();
    currentStage_++;
}

void AxisTestTask::waitForCalibrationFinish() {
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

void AxisTestTask::moveAxisToMinLimitPosition() {
    axisController_.moveToMinLimitPosition();
    axisMoveStartTimestampInMillis_ =
        systemClock_.getMillisecondsSinceStart();

    currentStage_++;
}

void AxisTestTask::waitForAxisAtMinLimitPosition() {
    const bool wasTimeoutReached =
        systemClock_.getMillisecondsSinceStart() -
            axisMoveStartTimestampInMillis_ >=
        axisMoveTimeoutInMillis_;

    const bool isAxisAtPosition = axisController_.isAtMinLimitPosition();

    if (wasTimeoutReached) {
        testResults_.startLimitSwitchSuccess = false;
        currentStage_++;
    } else if (isAxisAtPosition) {
        testResults_.startLimitSwitchSuccess = true;
        currentStage_++;
    }
}

void AxisTestTask::moveAxisToMaxLimitPosition() {
    axisController_.moveToMaxLimitPosition();
    axisMoveStartTimestampInMillis_ =
        systemClock_.getMillisecondsSinceStart();

    currentStage_++;
}

void AxisTestTask::waitForAxisAtMaxLimitPosition() {
    const bool wasTimeoutReached =
        systemClock_.getMillisecondsSinceStart() -
            axisMoveStartTimestampInMillis_ >=
        axisMoveTimeoutInMillis_;

    const bool isAxisAtPosition = axisController_.isAtMaxLimitPosition();

    if (wasTimeoutReached) {
        testResults_.endLimitSwitchSuccess = false;
        currentStage_++;
    } else if (isAxisAtPosition) {
        testResults_.endLimitSwitchSuccess = true;
        currentStage_++;
    }
}

void AxisTestTask::finishTask() {
    testResults_.motorDriverSuccess = !axisController_.wasFaultReported();

    state_ = TaskState::FINISHED;
}

const std::array<AxisTestTask::stageMethod, 7> AxisTestTask::stages_ {
    &AxisTestTask::calibrateAxes,
    &AxisTestTask::waitForCalibrationFinish,
    &AxisTestTask::moveAxisToMinLimitPosition,
    &AxisTestTask::waitForAxisAtMinLimitPosition,
    &AxisTestTask::moveAxisToMaxLimitPosition,
    &AxisTestTask::waitForAxisAtMaxLimitPosition,
    &AxisTestTask::finishTask
};

AxisTestTask::AxisTestTask(
    IConsumableTask<bool>& calibrationTask,
    IAxisController& axisController,
    ISystemClock& systemClock,
    uint32_t axisMoveTimeoutInMillis
) :
    calibrationTask_(calibrationTask),
    axisController_(axisController),
    systemClock_(systemClock),
    axisMoveTimeoutInMillis_(axisMoveTimeoutInMillis) {}

void AxisTestTask::start() {
    state_ = TaskState::RUNNING;
}

void AxisTestTask::reset() {
    axisController_.cancelMovement();

    state_ = TaskState::IDLE;
    currentStage_ = 0;

    testResults_.startLimitSwitchSuccess = false;
    testResults_.endLimitSwitchSuccess = false;
    testResults_.motorDriverSuccess = false;
}

void AxisTestTask::tick() {
    if (state_ != TaskState::RUNNING) {
        return;
    }

    std::invoke(stages_.at(currentStage_), this);
}

bool AxisTestTask::isFinished() const {
    return state_ == TaskState::FINISHED;
}

AxisTestResults AxisTestTask::consumeResult() {
    if (state_ != TaskState::FINISHED) {
        return AxisTestResults {
            .startLimitSwitchSuccess = false,
            .endLimitSwitchSuccess = false,
            .motorDriverSuccess = false
        };
    }

    const AxisTestResults result = testResults_;
    reset();

    return result;
}
};