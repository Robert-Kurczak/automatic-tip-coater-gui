#include "AxisConfigurator.hpp"

namespace ATC {
AxisConfigurator::AxisConfigurator(
    ILogger& logger,
    IAxisController& axisController,
    uint8_t positionStep,
    uint8_t speedStep
) :
    logger_(logger),
    axisController_(axisController),
    positionStep_(positionStep),
    speedStep_(speedStep) {}

void AxisConfigurator::showcaseStartPosition() {
    axisController_.moveToStartPosition();
}

void AxisConfigurator::increaseStartPosition() {
    axisController_.setStartPosition(
        axisController_.getStartPosition() + positionStep_
    );

    showcaseStartPosition();
}

void AxisConfigurator::decreaseStartPosition() {
    axisController_.setStartPosition(
        axisController_.getStartPosition() - positionStep_
    );

    showcaseStartPosition();
}

void AxisConfigurator::saveStartPosition() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
}

uint32_t AxisConfigurator::getStartPosition() const {
    return axisController_.getStartPosition();
}

void AxisConfigurator::showcaseEndPosition() {
    axisController_.moveToEndPosition();
}

void AxisConfigurator::increaseEndPosition() {
    axisController_.setEndPosition(
        axisController_.getStartPosition() + positionStep_
    );

    showcaseEndPosition();
}

void AxisConfigurator::decreaseEndPosition() {
    axisController_.setEndPosition(
        axisController_.getStartPosition() - positionStep_
    );

    showcaseEndPosition();
}

void AxisConfigurator::saveEndPosition() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
}

uint32_t AxisConfigurator::getEndPosition() const {
    return axisController_.getEndPosition();
}

void AxisConfigurator::showcaseSpeed() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
}

void AxisConfigurator::increaseSpeed() {
    axisController_.setSpeed(axisController_.getSpeed() + speedStep_);
}

void AxisConfigurator::decreaseSpeed() {
    axisController_.setSpeed(axisController_.getSpeed() - speedStep_);
}

void AxisConfigurator::saveSpeed() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
}

uint32_t AxisConfigurator::getSpeed() const {
    return axisController_.getSpeed();
}
}