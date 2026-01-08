#include "AxisConfiguratorService.hpp"

namespace ATC {
IPersistentStorageController& AxisConfiguratorService::
    getPersistentStorageController() {
    return persistentStorageController_;
}

AxisPersistentConfig& AxisConfiguratorService::
    getBufferedPersistentConfig() {
    return bufferedPersistentConfig_;
}

AxisConfiguratorService::AxisConfiguratorService(
    IPersistentStorageController& persistentStorageController,
    IAxisController& axisController,
    const AxisConfiguratorParameters& parameters
) :
    persistentStorageController_(persistentStorageController),
    axisController_(axisController),
    parameters_(parameters) {}

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
    bufferedPersistentConfig_.startPosition += parameters_.positionStep;
    showcaseStartPosition();
}

void AxisConfiguratorService::decreaseStartPosition() {
    bufferedPersistentConfig_.startPosition -= parameters_.positionStep;
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
    bufferedPersistentConfig_.endPosition += parameters_.positionStep;
    showcaseEndPosition();
}

void AxisConfiguratorService::decreaseEndPosition() {
    bufferedPersistentConfig_.endPosition -= parameters_.positionStep;
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
    constexpr uint8_t errorMargin = 10;

    const uint32_t currentPosition = axisController_.getCurrentPosition();

    const bool isAtShowcasePosition =
        currentPosition <=
            parameters_.speedShowcasePosition + errorMargin &&
        currentPosition >=
            parameters_.speedShowcasePosition - errorMargin;

    if (isAtShowcasePosition) {
        axisController_.moveToStartPosition();
    } else {
        axisController_.moveToPosition(parameters_.speedShowcasePosition);
    }
}

void AxisConfiguratorService::increaseSpeed() {
    bufferedPersistentConfig_.speed += parameters_.speedStep;
}

void AxisConfiguratorService::decreaseSpeed() {
    bufferedPersistentConfig_.speed -= parameters_.speedStep;
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