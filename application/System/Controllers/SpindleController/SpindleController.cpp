#include "SpindleController.hpp"

namespace ATC {
SpindleController::SpindleController(ILogger& logger, IMotor& motor) :
    logger_(logger),
    motor_(motor) {}

void SpindleController::tick() {}

void SpindleController::init() {
    motor_.init();
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
    startTimedRotation(rotationTimeMillis_);
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

void SpindleController::setRotationTimeMillis(uint32_t value) {}

uint32_t SpindleController::getRotationTimeMillis() const {
    return rotationTimeMillis_;
}
}