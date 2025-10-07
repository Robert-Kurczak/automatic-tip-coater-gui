#include "SpindleConfiguratorService.hpp"

namespace ATC {
SpindleConfiguratorService::SpindleConfiguratorService(
    ILogger& logger,
    ISpindleController& spindleController,
    uint32_t showcaseRotationTimeInMillis,
    uint8_t speedPercentStep,
    uint32_t rotationTimeStepInMillis
) :
    logger_(logger),
    spindleController_(spindleController),
    showcaseRotationTimeInMillis_(showcaseRotationTimeInMillis),
    speedPercentStep_(speedPercentStep),
    rotationTimeStepInMillis_(rotationTimeStepInMillis) {}

void SpindleConfiguratorService::resetBufferedConfig() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
}

void SpindleConfiguratorService::showcaseRotation() {
    spindleController_.startTimedRotation(showcaseRotationTimeInMillis_);
}

void SpindleConfiguratorService::increaseSpeedPercent() {
    spindleController_.setSpeedPercent(
        spindleController_.getSpeedPercent() + speedPercentStep_
    );
}

void SpindleConfiguratorService::decreaseSpeedPercent() {
    spindleController_.setSpeedPercent(
        spindleController_.getSpeedPercent() - speedPercentStep_
    );
}

void SpindleConfiguratorService::saveSpeedPercent() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
}

uint8_t SpindleConfiguratorService::getSpeedPercent() const {
    return spindleController_.getSpeedPercent();
}

void SpindleConfiguratorService::setDirectionClockwise() {
    spindleController_.setDirectionClockwise();
}

void SpindleConfiguratorService::setDirectionCounterClockwise() {
    spindleController_.setDirectionCounterClockwise();
}

void SpindleConfiguratorService::saveDirection() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
}

bool SpindleConfiguratorService::isDirectionClockwise() const {
    return spindleController_.isDirectionClockwise();
}

void SpindleConfiguratorService::increaseRotationTimeInMillis() {
    spindleController_.setRotationTimeInMillis(
        spindleController_.getRotationTimeInMillis() +
        rotationTimeStepInMillis_
    );
}

void SpindleConfiguratorService::decreaseRotationTimeInMillis() {
    spindleController_.setRotationTimeInMillis(
        spindleController_.getRotationTimeInMillis() -
        rotationTimeStepInMillis_
    );
}

void SpindleConfiguratorService::saveRotationTimeInMillis() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
}

uint32_t SpindleConfiguratorService::getRotationTimeInMillis() const {
    return spindleController_.getRotationTimeInMillis();
}
}
