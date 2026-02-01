#include "AxisConfiguratorService.hpp"

#include "application/System/Controllers/PersistentStorageController/PersistentData/AxisPersistentConfig.hpp"

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
    bufferedPersistentConfig_.startPositionInMicrometers +=
        parameters_.positionStep;
    showcaseStartPosition();
}

void AxisConfiguratorService::decreaseStartPosition() {
    bufferedPersistentConfig_.startPositionInMicrometers -=
        parameters_.positionStep;
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
    bufferedPersistentConfig_.endPositionInMicrometers +=
        parameters_.positionStep;
    showcaseEndPosition();
}

void AxisConfiguratorService::decreaseEndPosition() {
    bufferedPersistentConfig_.endPositionInMicrometers -=
        parameters_.positionStep;
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

    const bool isAtShowcasePosition =
        currentPosition <=
            parameters_.speedShowcasePosition + errorMargin &&
        currentPosition >=
            parameters_.speedShowcasePosition - errorMargin;

    if (isAtShowcasePosition) {
        axisController_.moveToStartPosition();
    } else {
        axisController_.moveToPositionInMicrometers(
            parameters_.speedShowcasePosition
        );
    }
}

void AxisConfiguratorService::increaseSpeed() {
    bufferedPersistentConfig_.speedInMillimetersPerSecond +=
        parameters_.speedStep;
}

void AxisConfiguratorService::decreaseSpeed() {
    bufferedPersistentConfig_.speedInMillimetersPerSecond -=
        parameters_.speedStep;
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
