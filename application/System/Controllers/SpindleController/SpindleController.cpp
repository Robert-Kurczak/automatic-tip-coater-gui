#include "SpindleController.hpp"

namespace ATC {
SpindleController::SpindleController(ILogger& logger, IMotor& motor) :
    logger_(logger),
    motor_(motor) {}

void SpindleController::init(const SpindlePersistentConfig& config) {
    speedPercent_ = config.speedPercentage;
    rotationTimeInMillis_ = config.timedRotationInMillis;

    motor_.init();
}

void SpindleController::tick() {}

bool SpindleController::wasFaultReported() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
    return false;
}

void SpindleController::startRotation() {
    motor_.startRotation(speedPercent_);
}

void SpindleController::startTimedRotation(uint32_t rotationMillis) {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
}

void SpindleController::startTimedRotation() {
    startTimedRotation(rotationTimeInMillis_);
}

void SpindleController::stopRotation() {
    motor_.stopRotation();
}

bool SpindleController::isTimedRotationFinished() const {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
    return true;
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