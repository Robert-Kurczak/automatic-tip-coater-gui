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
    bufferedPersistentConfig_.startPosition =
        axisController_.getStartPosition();
    bufferedPersistentConfig_.endPosition =
        axisController_.getEndPosition();
    bufferedPersistentConfig_.speed = axisController_.getSpeed();
}

void AxisConfiguratorService::showcaseStartPosition() {
    axisController_.moveToPosition(
        bufferedPersistentConfig_.startPosition
    );
}

void AxisConfiguratorService::increaseStartPosition() {
    bufferedPersistentConfig_.startPosition += positionStep_;
    showcaseStartPosition();
}

void AxisConfiguratorService::decreaseStartPosition() {
    bufferedPersistentConfig_.startPosition -= positionStep_;
    showcaseStartPosition();
}

void AxisConfiguratorService::saveStartPosition() {
    axisController_.setStartPosition(
        bufferedPersistentConfig_.startPosition
    );
    saveConfigToPersistentMemory();
}

uint32_t AxisConfiguratorService::getStartPosition() const {
    return bufferedPersistentConfig_.startPosition;
}

void AxisConfiguratorService::showcaseEndPosition() {
    axisController_.moveToPosition(bufferedPersistentConfig_.endPosition);
}

void AxisConfiguratorService::increaseEndPosition() {
    bufferedPersistentConfig_.endPosition += positionStep_;
    showcaseEndPosition();
}

void AxisConfiguratorService::decreaseEndPosition() {
    bufferedPersistentConfig_.endPosition -= positionStep_;
    showcaseEndPosition();
}

void AxisConfiguratorService::saveEndPosition() {
    axisController_.setEndPosition(bufferedPersistentConfig_.endPosition);
    saveConfigToPersistentMemory();
}

uint32_t AxisConfiguratorService::getEndPosition() const {
    return bufferedPersistentConfig_.endPosition;
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
    bufferedPersistentConfig_.speed += speedStep_;
}

void AxisConfiguratorService::decreaseSpeed() {
    bufferedPersistentConfig_.speed -= speedStep_;
}

void AxisConfiguratorService::saveSpeed() {
    axisController_.setSpeed(bufferedPersistentConfig_.speed);
    showcaseSpeed();
    saveConfigToPersistentMemory();
}

uint32_t AxisConfiguratorService::getSpeed() const {
    return bufferedPersistentConfig_.speed;
}
}