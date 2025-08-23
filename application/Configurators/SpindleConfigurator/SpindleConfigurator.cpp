#include "SpindleConfigurator.hpp"

namespace ATC {
SpindleConfigurator::SpindleConfigurator(
    ILogger& logger,
    ISpindleController& spindleController,
    uint8_t showcaseRotationTimeMillis,
    uint8_t speedPercentStep,
    uint8_t rotationTimeStep
) :
    logger_(logger),
    spindleController_(spindleController),
    showcaseRotationTimeMillis_(showcaseRotationTimeMillis),
    speedPercentStep_(speedPercentStep),
    rotationTimeStep_(rotationTimeStep) {}

void SpindleConfigurator::showcaseRotation() {
    spindleController_.startTimedRotation(showcaseRotationTimeMillis_);
}

void SpindleConfigurator::increaseSpeedPercent() {
    spindleController_.setSpeedPercent(
        spindleController_.getSpeedPercent() + speedPercentStep_
    );
}

void SpindleConfigurator::decreaseSpeedPercent() {
    spindleController_.setSpeedPercent(
        spindleController_.getSpeedPercent() - speedPercentStep_
    );
}

void SpindleConfigurator::saveSpeedPercent() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
}

uint8_t SpindleConfigurator::getSpeedPercent() const {
    return spindleController_.getSpeedPercent();
}

void SpindleConfigurator::setDirectionClockwise() {
    spindleController_.setDirectionClockwise();
}

void SpindleConfigurator::setDirectionCounterClockwise() {
    spindleController_.setDirectionCounterClockwise();
}

void SpindleConfigurator::saveDirection() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
}

bool SpindleConfigurator::isDirectionClockwise() const {
    return spindleController_.isDirectionClockwise();
}

void SpindleConfigurator::increaseRotationTime() {
    spindleController_.setRotationTimeMillis(
        spindleController_.getRotationTimeMillis() + rotationTimeStep_
    );
}

void SpindleConfigurator::decreaseRotationTime() {
    spindleController_.setRotationTimeMillis(
        spindleController_.getRotationTimeMillis() - rotationTimeStep_
    );
}

void SpindleConfigurator::saveRotationTime() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
}

uint32_t SpindleConfigurator::getRotationTimeMillis() const {
    return spindleController_.getRotationTimeMillis();
}
}