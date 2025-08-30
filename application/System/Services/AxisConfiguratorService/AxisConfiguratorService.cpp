#include "AxisConfiguratorService.hpp"

namespace ATC {
AxisConfiguratorService::AxisConfiguratorService(
    ILogger& logger,
    IAxisController& axisController,
    uint8_t positionStep,
    uint8_t speedStep
) :
    logger_(logger),
    axisController_(axisController),
    positionStep_(positionStep),
    speedStep_(speedStep) {}

void AxisConfiguratorService::showcaseStartPosition() {
    axisController_.moveToStartPosition();
}

void AxisConfiguratorService::increaseStartPosition() {
    axisController_.setStartPosition(
        axisController_.getStartPosition() + positionStep_
    );

    showcaseStartPosition();
}

void AxisConfiguratorService::decreaseStartPosition() {
    axisController_.setStartPosition(
        axisController_.getStartPosition() - positionStep_
    );

    showcaseStartPosition();
}

void AxisConfiguratorService::saveStartPosition() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
}

uint32_t AxisConfiguratorService::getStartPosition() const {
    return axisController_.getStartPosition();
}

void AxisConfiguratorService::showcaseEndPosition() {
    axisController_.moveToEndPosition();
}

void AxisConfiguratorService::increaseEndPosition() {
    axisController_.setEndPosition(
        axisController_.getStartPosition() + positionStep_
    );

    showcaseEndPosition();
}

void AxisConfiguratorService::decreaseEndPosition() {
    axisController_.setEndPosition(
        axisController_.getStartPosition() - positionStep_
    );

    showcaseEndPosition();
}

void AxisConfiguratorService::saveEndPosition() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
}

uint32_t AxisConfiguratorService::getEndPosition() const {
    return axisController_.getEndPosition();
}

void AxisConfiguratorService::showcaseSpeed() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
}

void AxisConfiguratorService::increaseSpeed() {
    axisController_.setSpeed(axisController_.getSpeed() + speedStep_);
}

void AxisConfiguratorService::decreaseSpeed() {
    axisController_.setSpeed(axisController_.getSpeed() - speedStep_);
}

void AxisConfiguratorService::saveSpeed() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
}

uint32_t AxisConfiguratorService::getSpeed() const {
    return axisController_.getSpeed();
}
}