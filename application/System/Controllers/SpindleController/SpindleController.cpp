#include "SpindleController.hpp"

namespace ATC {
SpindleController::SpindleController(
    ILoggerSink& loggerSink,
    ISystemClock& systemClock,
    IMotorDriver& motorDriver
) :
    loggerSink_(loggerSink),
    systemClock_(systemClock),
    motorDriver_(motorDriver) {}

void SpindleController::checkMotorFault() {
    if (!wasFaultReported_ && motorDriver_.isFaultDetected()) {
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
    speedPercent_ = config.speedPercent;
    rotationTimeInMillis_ = config.timedRotationInMillis;

    motorDriver_.init();

    if (config.isDirectionClockwise) {
        motorDriver_.setDirectionClockwise();
    } else {
        motorDriver_.setDirectionCounterClockwise();
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
    motorDriver_.startRotation(speedPercent_);
}

void SpindleController::startTimedRotation(uint32_t rotationMillis) {
    timedRotationEndTimestamp_ =
        systemClock_.getMillisecondsSinceStart() + rotationMillis;
    timedRotationStarted_ = true;

    motorDriver_.startRotation(speedPercent_);
}

void SpindleController::startTimedRotation() {
    startTimedRotation(rotationTimeInMillis_);
}

void SpindleController::stopRotation() {
    motorDriver_.stopRotation();
}

bool SpindleController::isTimedRotationFinished() const {
    return !timedRotationStarted_;
}

void SpindleController::setDirectionClockwise() {
    motorDriver_.setDirectionClockwise();
}

void SpindleController::setDirectionCounterClockwise() {
    motorDriver_.setDirectionCounterClockwise();
}

bool SpindleController::isDirectionClockwise() const {
    return motorDriver_.isDirectionClockwise();
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
