#include "AxisConfiguratorService.hpp"

#include "application/System/Controllers/PersistentStorageController/PersistentData/AxisPersistentConfig.hpp"

#include <algorithm>

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
    bufferedPersistentConfig_.startPositionInMicrometers =
        axisController_.getStartPositionInMicrometers();
    bufferedPersistentConfig_.endPositionInMicrometers =
        axisController_.getEndPositionInMicrometers();
    bufferedPersistentConfig_.speedInMillimetersPerSecond =
        axisController_.getSpeedInMillimetersPerSecond();
}

void AxisConfiguratorService::showcaseStartPosition() {
    axisController_.moveToPositionInMicrometers(
        bufferedPersistentConfig_.startPositionInMicrometers
    );
}

void AxisConfiguratorService::increaseStartPosition() {
    uint32_t& currentValue =
        bufferedPersistentConfig_.startPositionInMicrometers;

    const uint32_t step = parameters_.positionStepInMicrometers;

    const uint32_t maxBound = std::min(
        bufferedPersistentConfig_.endPositionInMicrometers,
        parameters_.maxPositionInMicrometers
    );

    if (currentValue > maxBound - step) {
        return;
    }

    currentValue += step;
    showcaseStartPosition();
}

void AxisConfiguratorService::decreaseStartPosition() {
    uint32_t& currentValue =
        bufferedPersistentConfig_.startPositionInMicrometers;

    const uint32_t step = parameters_.positionStepInMicrometers;
    const uint32_t minBound = parameters_.minPositionInMicrometers;

    if (currentValue < minBound + step) {
        return;
    }

    currentValue -= step;
    showcaseStartPosition();
}

void AxisConfiguratorService::saveStartPosition() {
    axisController_.setStartPositionInMicrometers(
        bufferedPersistentConfig_.startPositionInMicrometers
    );
    saveConfigToPersistentMemory();
}

uint32_t AxisConfiguratorService::getStartPositionInMicrometers() const {
    return bufferedPersistentConfig_.startPositionInMicrometers;
}

void AxisConfiguratorService::showcaseEndPosition() {
    axisController_.moveToPositionInMicrometers(
        bufferedPersistentConfig_.endPositionInMicrometers
    );
}

void AxisConfiguratorService::increaseEndPosition() {
    uint32_t& currentValue =
        bufferedPersistentConfig_.endPositionInMicrometers;

    const uint32_t step = parameters_.positionStepInMicrometers;

    const uint32_t maxBound = parameters_.maxPositionInMicrometers;

    if (currentValue > maxBound - step) {
        return;
    }

    currentValue += step;
    showcaseEndPosition();
}

void AxisConfiguratorService::decreaseEndPosition() {
    uint32_t& currentValue =
        bufferedPersistentConfig_.endPositionInMicrometers;

    const uint32_t step = parameters_.positionStepInMicrometers;

    const uint32_t minBound = std::max(
        bufferedPersistentConfig_.startPositionInMicrometers,
        parameters_.minPositionInMicrometers
    );

    if (currentValue < minBound + step) {
        return;
    }

    currentValue -= step;
    showcaseEndPosition();
}

void AxisConfiguratorService::saveEndPosition() {
    axisController_.setEndPositionInMicrometers(
        bufferedPersistentConfig_.endPositionInMicrometers
    );
    saveConfigToPersistentMemory();
}

uint32_t AxisConfiguratorService::getEndPositionInMicrometers() const {
    return bufferedPersistentConfig_.endPositionInMicrometers;
}

void AxisConfiguratorService::showcaseSpeed() {
    constexpr uint8_t errorMargin = 10;

    const uint32_t currentPosition =
        axisController_.getCurrentPositionInMicrometers();

    const uint32_t showcasePosition =
        parameters_.speedShowcasePositionInMicrometers;

    const bool isAtShowcasePosition =
        currentPosition <= showcasePosition + errorMargin &&
        currentPosition >= showcasePosition - errorMargin;

    if (isAtShowcasePosition) {
        axisController_.moveToStartPosition();
    } else {
        axisController_.moveToPositionInMicrometers(
            parameters_.speedShowcasePositionInMicrometers
        );
    }
}

void AxisConfiguratorService::increaseSpeed() {
    uint16_t& currentValue =
        bufferedPersistentConfig_.speedInMillimetersPerSecond;

    const uint16_t step = parameters_.speedStepInMillimetersPerSecond;
    const uint16_t maxBound = parameters_.maxSpeedInMillimetersPerSecond;

    if (currentValue > maxBound - step) {
        return;
    }

    currentValue += step;
}

void AxisConfiguratorService::decreaseSpeed() {
    uint16_t& currentValue =
        bufferedPersistentConfig_.speedInMillimetersPerSecond;

    const uint16_t step = parameters_.speedStepInMillimetersPerSecond;
    const uint16_t minBound = parameters_.minSpeedInMillimetersPerSecond;

    if (currentValue < minBound + step) {
        return;
    }

    currentValue -= step;
}

void AxisConfiguratorService::saveSpeed() {
    axisController_.setSpeedInMillimetersPerSecond(
        bufferedPersistentConfig_.speedInMillimetersPerSecond
    );
    showcaseSpeed();
    saveConfigToPersistentMemory();
}

uint32_t AxisConfiguratorService::getSpeedInMillimetersPerSecond() const {
    return bufferedPersistentConfig_.speedInMillimetersPerSecond;
}

[[nodiscard]] AxisPersistentConfig AxisConfiguratorService::
    getStoredConfig() const {
    return AxisPersistentConfig {
        .startPositionInMicrometers =
            axisController_.getStartPositionInMicrometers(),
        .endPositionInMicrometers =
            axisController_.getEndPositionInMicrometers(),
        .speedInMillimetersPerSecond =
            axisController_.getSpeedInMillimetersPerSecond()
    };
}
}
