#include "SpindleController.hpp"

#include "application/Utils/Logger.hpp"

namespace ATC {
SpindleController::SpindleController(
    ILoggerSink& loggerSink,
    ISystemClock& systemClock,
    IMotor& motor
) :
    loggerSink_(loggerSink),
    systemClock_(systemClock),
    motor_(motor) {}

void SpindleController::checkMotorFault() {
    if (!wasFaultReported_ && motor_.isFaultDetected()) {
        wasFaultReported_ = true;
    }
}

void SpindleController::checkTimedRotation() {
    if (!timedRotationStarted_) {
        return;
    }

    const uint32_t currentTimestampMillis =
        systemClock_.getMillisecondsSinceStart();

    if (currentTimestampMillis >= timedRotationEndTimestamp_) {
        timedRotationStarted_ = false;
        stopRotation();
    }
}

void SpindleController::init(const SpindlePersistentConfig& config) {
    speedPercent_ = config.speedPercentage;
    rotationTimeInMillis_ = config.timedRotationInMillis;

    motor_.init();

    if (config.isDirectionClockwise) {
        motor_.setDirectionClockwise();
    } else {
        motor_.setDirectionCounterClockwise();
    }
}

void SpindleController::tick() {
    checkMotorFault();
    checkTimedRotation();
}

bool SpindleController::wasFaultReported() {
    return wasFaultReported_;
}

void SpindleController::startRotation() {
    motor_.startRotation(speedPercent_);
}

void SpindleController::startTimedRotation(uint32_t rotationMillis) {
    timedRotationEndTimestamp_ =
        systemClock_.getMillisecondsSinceStart() + rotationMillis;
    timedRotationStarted_ = true;

    motor_.startRotation(speedPercent_);
}

void SpindleController::startTimedRotation() {
    startTimedRotation(rotationTimeInMillis_);
}

void SpindleController::stopRotation() {
    motor_.stopRotation();
}

bool SpindleController::isTimedRotationFinished() const {
    return !timedRotationStarted_;
}

void SpindleController::setDirectionClockwise() {
    motor_.setDirectionClockwise();
}

void SpindleController::setDirectionCounterClockwise() {
    motor_.setDirectionCounterClockwise();
}

bool SpindleController::isDirectionClockwise() const {
    return motor_.isDirectionClockwise();
}

void SpindleController::setSpeedPercent(uint8_t value) {
    speedPercent_ = value;
}

uint8_t SpindleController::getSpeedPercent() const {
    return speedPercent_;
}

void SpindleController::setRotationTimeInMillis(uint32_t value) {
    rotationTimeInMillis_ = value;
}

uint32_t SpindleController::getRotationTimeInMillis() const {
    return rotationTimeInMillis_;
}
}