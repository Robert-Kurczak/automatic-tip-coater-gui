#include "AxisConfiguratorService.hpp"

namespace ATC {
AxisConfiguratorService::AxisConfiguratorService(
    IPersistentStorageController& persistentStorageController,
    IAxisController& axisController,
    uint8_t positionStep,
    uint8_t speedStep,
    uint32_t speedShowcasePosition
) :
    persistentStorageController_(persistentStorageController),
    axisController_(axisController),
    positionStep_(positionStep),
    speedStep_(speedStep),
    speedShowcasePosition_(speedShowcasePosition) {}

void AxisConfiguratorService::resetBufferedConfig() {
    bufferedStartPosition_ = axisController_.getStartPosition();
    bufferedEndPosition_ = axisController_.getEndPosition();
    bufferedSpeed_ = axisController_.getSpeed();
}

void AxisConfiguratorService::showcaseStartPosition() {
    axisController_.moveToPosition(bufferedStartPosition_);
}

void AxisConfiguratorService::increaseStartPosition() {
    bufferedStartPosition_ += positionStep_;
    showcaseStartPosition();
}

void AxisConfiguratorService::decreaseStartPosition() {
    bufferedStartPosition_ -= positionStep_;
    showcaseStartPosition();
}

void AxisConfiguratorService::saveStartPosition() {
    axisController_.setStartPosition(bufferedStartPosition_);
    saveConfigToPersistentMemory();
}

uint32_t AxisConfiguratorService::getStartPosition() const {
    return bufferedStartPosition_;
}

void AxisConfiguratorService::showcaseEndPosition() {
    axisController_.moveToPosition(bufferedEndPosition_);
}

void AxisConfiguratorService::increaseEndPosition() {
    bufferedEndPosition_ += positionStep_;
    showcaseEndPosition();
}

void AxisConfiguratorService::decreaseEndPosition() {
    bufferedEndPosition_ -= positionStep_;
    showcaseEndPosition();
}

void AxisConfiguratorService::saveEndPosition() {
    axisController_.setEndPosition(bufferedEndPosition_);
    saveConfigToPersistentMemory();
}

uint32_t AxisConfiguratorService::getEndPosition() const {
    return bufferedEndPosition_;
}

void AxisConfiguratorService::showcaseSpeed() {
    const uint32_t currentPosition = axisController_.getCurrentPosition();
    const uint8_t errorMargin = 10;

    const bool isAtShowcasePosition =
        currentPosition <= speedShowcasePosition_ + errorMargin &&
        currentPosition >= speedShowcasePosition_ - errorMargin;

    if (isAtShowcasePosition) {
        axisController_.moveToStartPosition();
    } else {
        axisController_.moveToPosition(speedShowcasePosition_);
    }
}

void AxisConfiguratorService::increaseSpeed() {
    bufferedSpeed_ += speedStep_;
}

void AxisConfiguratorService::decreaseSpeed() {
    bufferedSpeed_ -= speedStep_;
}

void AxisConfiguratorService::saveSpeed() {
    axisController_.setSpeed(bufferedSpeed_);
    showcaseSpeed();
    saveConfigToPersistentMemory();
}

uint32_t AxisConfiguratorService::getSpeed() const {
    return bufferedSpeed_;
}
}