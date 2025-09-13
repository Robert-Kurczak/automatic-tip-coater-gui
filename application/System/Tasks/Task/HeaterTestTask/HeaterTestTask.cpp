#include "HeaterTestTask.hpp"

namespace ATC {
void HeaterTestTask::turnHeaterOn() {
    heaterController_.turnOn();

    heatingStartTimestampInMillis_ =
        systemClock_.getMillisecondsSinceStart();

    currentStage_++;
}

void HeaterTestTask::waitForTargetTemperature() {
    const bool wasTimeoutReached =
        systemClock_.getMillisecondsSinceStart() -
            heatingStartTimestampInMillis_ >=
        heatingTimeoutInMillis_;

    const bool wasTargetTemperatureReached =
        heaterController_.isAtTargetTemperature();

    if (wasTimeoutReached) {
        testResults_.temperatureSuccess = false;
        currentStage_++;
    } else if (wasTargetTemperatureReached) {
        testResults_.temperatureSuccess = true;
        currentStage_++;
    }
}

void HeaterTestTask::finishTask() {
    heaterController_.turnOff();

    state_ = TaskState::FINISHED;
}

HeaterTestTask::HeaterTestTask(
    IHeaterController& heaterController,
    ISystemClock& systemClock,
    uint32_t heatingTimeoutInMillis
) :
    heaterController_(heaterController),
    systemClock_(systemClock),
    heatingTimeoutInMillis_(heatingTimeoutInMillis) {}

void HeaterTestTask::start() {
    state_ = TaskState::RUNNING;
}

void HeaterTestTask::reset() {
    state_ = TaskState::IDLE;
    currentStage_ = 0;
    heaterController_.turnOff();

    testResults_.temperatureSuccess = false;
}

void HeaterTestTask::tick() {
    if (state_ != TaskState::RUNNING) {
        return;
    }

    std::invoke(stages_[currentStage_], this);
}

bool HeaterTestTask::isFinished() const {
    return state_ == TaskState::FINISHED;
}

HeaterTestResults HeaterTestTask::consumeResult() {
    if (state_ != TaskState::FINISHED) {
        return HeaterTestResults {
            .temperatureSuccess = false,
        };
    }

    const HeaterTestResults result = testResults_;
    reset();

    return result;
}
};
