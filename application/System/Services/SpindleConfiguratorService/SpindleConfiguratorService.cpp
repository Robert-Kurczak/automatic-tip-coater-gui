#include "SpindleConfiguratorService.hpp"

#include "application/System/Services/SpindleConfiguratorService/SpindleConfiguratorParameters.hpp"

namespace ATC {
SpindleConfiguratorService::SpindleConfiguratorService(
    IPersistentStorageController& persistentStorageController,
    ISpindleController& spindleController,
    SpindleConfiguratorParameters parameters
) :
    persistentStorageController_(persistentStorageController),
    spindleController_(spindleController),
    parameters_(parameters) {}

void SpindleConfiguratorService::resetBufferedConfig() {
    bufferedPersistentConfig_.speedPercent =
        spindleController_.getSpeedPercent();

    bufferedPersistentConfig_.isDirectionClockwise =
        spindleController_.isDirectionClockwise();

    bufferedPersistentConfig_.timedRotationInMillis =
        spindleController_.getRotationTimeInMillis();
}

void SpindleConfiguratorService::showcaseRotation() {
    spindleController_.startTimedRotation(
        parameters_.showcaseRotationTimeMillis
    );
}

void SpindleConfiguratorService::increaseSpeedPercent() {
    bufferedPersistentConfig_.speedPercent +=
        parameters_.speedPercentStep;
}

void SpindleConfiguratorService::decreaseSpeedPercent() {
    bufferedPersistentConfig_.speedPercent -=
        parameters_.speedPercentStep;
}

void SpindleConfiguratorService::saveSpeedPercent() {
    spindleController_.setSpeedPercent(
        bufferedPersistentConfig_.speedPercent
    );

    persistentStorageController_.saveSpindleConfig(
        bufferedPersistentConfig_
    );
}

uint8_t SpindleConfiguratorService::getSpeedPercent() const {
    return bufferedPersistentConfig_.speedPercent;
}

void SpindleConfiguratorService::setDirectionClockwise() {
    bufferedPersistentConfig_.isDirectionClockwise = true;
}

void SpindleConfiguratorService::setDirectionCounterClockwise() {
    bufferedPersistentConfig_.isDirectionClockwise = false;
}

void SpindleConfiguratorService::saveDirection() {
    if (bufferedPersistentConfig_.isDirectionClockwise) {
        spindleController_.setDirectionClockwise();
    } else {
        spindleController_.setDirectionCounterClockwise();
    }

    persistentStorageController_.saveSpindleConfig(
        bufferedPersistentConfig_
    );
}

bool SpindleConfiguratorService::isDirectionClockwise() const {
    return bufferedPersistentConfig_.isDirectionClockwise;
}

void SpindleConfiguratorService::increaseRotationTimeInMillis() {
    bufferedPersistentConfig_.timedRotationInMillis +=
        parameters_.rotationTimeStepMillis;
}

void SpindleConfiguratorService::decreaseRotationTimeInMillis() {
    bufferedPersistentConfig_.timedRotationInMillis -=
        parameters_.rotationTimeStepMillis;
}

void SpindleConfiguratorService::saveRotationTimeInMillis() {
    spindleController_.setRotationTimeInMillis(
        bufferedPersistentConfig_.timedRotationInMillis
    );

    persistentStorageController_.saveSpindleConfig(
        bufferedPersistentConfig_
    );
}

uint32_t SpindleConfiguratorService::getRotationTimeInMillis() const {
    return bufferedPersistentConfig_.timedRotationInMillis;
}

SpindlePersistentConfig SpindleConfiguratorService::
    getStoredConfig() const {
    return SpindlePersistentConfig {
        .speedPercent = spindleController_.getSpeedPercent(),
        .isDirectionClockwise = spindleController_.isDirectionClockwise(),
        .timedRotationInMillis =
            spindleController_.getRotationTimeInMillis()
    };
}
}
