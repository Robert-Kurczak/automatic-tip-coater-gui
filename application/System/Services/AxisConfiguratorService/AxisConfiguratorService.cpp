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
    bufferedConfig_.startPosition = axisController_.getStartPosition();
    bufferedConfig_.endPosition = axisController_.getEndPosition();
    bufferedConfig_.speed = axisController_.getSpeed();
}

void AxisConfiguratorService::showcaseStartPosition() {
    axisController_.moveToPosition(bufferedConfig_.startPosition);
}

void AxisConfiguratorService::increaseStartPosition() {
    bufferedConfig_.startPosition += positionStep_;
    showcaseStartPosition();
}

void AxisConfiguratorService::decreaseStartPosition() {
    bufferedConfig_.startPosition -= positionStep_;
    showcaseStartPosition();
}

void AxisConfiguratorService::saveStartPosition() {
    axisController_.setStartPosition(bufferedConfig_.startPosition);
    saveConfigToPersistentMemory();
}

uint32_t AxisConfiguratorService::getStartPosition() const {
    return bufferedConfig_.startPosition;
}

void AxisConfiguratorService::showcaseEndPosition() {
    axisController_.moveToPosition(bufferedConfig_.endPosition);
}

void AxisConfiguratorService::increaseEndPosition() {
    bufferedConfig_.endPosition += positionStep_;
    showcaseEndPosition();
}

void AxisConfiguratorService::decreaseEndPosition() {
    bufferedConfig_.endPosition -= positionStep_;
    showcaseEndPosition();
}

void AxisConfiguratorService::saveEndPosition() {
    axisController_.setEndPosition(bufferedConfig_.endPosition);
    saveConfigToPersistentMemory();
}

uint32_t AxisConfiguratorService::getEndPosition() const {
    return bufferedConfig_.endPosition;
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
    bufferedConfig_.speed += speedStep_;
}

void AxisConfiguratorService::decreaseSpeed() {
    bufferedConfig_.speed -= speedStep_;
}

void AxisConfiguratorService::saveSpeed() {
    axisController_.setSpeed(bufferedConfig_.speed);
    showcaseSpeed();
    saveConfigToPersistentMemory();
}

uint32_t AxisConfiguratorService::getSpeed() const {
    return bufferedConfig_.speed;
}
}