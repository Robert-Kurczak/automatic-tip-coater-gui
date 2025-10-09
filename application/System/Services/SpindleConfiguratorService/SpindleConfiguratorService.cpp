#include "SpindleConfiguratorService.hpp"

namespace ATC {
SpindleConfiguratorService::SpindleConfiguratorService(
    IPersistentStorageController& persistentStorageController,
    ISpindleController& spindleController,
    uint32_t showcaseRotationTimeInMillis,
    uint8_t speedPercentStep,
    uint32_t rotationTimeStepInMillis
) :
    persistentStorageController_(persistentStorageController),
    spindleController_(spindleController),
    showcaseRotationTimeInMillis_(showcaseRotationTimeInMillis),
    speedPercentStep_(speedPercentStep),
    rotationTimeStepInMillis_(rotationTimeStepInMillis) {}

void SpindleConfiguratorService::resetBufferedConfig() {
    bufferedPersistentConfig_.speedPercentage =
        spindleController_.getSpeedPercent();

    bufferedPersistentConfig_.isDirectionClockwise =
        spindleController_.isDirectionClockwise();

    bufferedPersistentConfig_.timedRotationInMillis =
        spindleController_.getRotationTimeInMillis();
}

void SpindleConfiguratorService::showcaseRotation() {
    spindleController_.startTimedRotation(showcaseRotationTimeInMillis_);
}

void SpindleConfiguratorService::increaseSpeedPercent() {
    bufferedPersistentConfig_.speedPercentage += speedPercentStep_;
}

void SpindleConfiguratorService::decreaseSpeedPercent() {
    bufferedPersistentConfig_.speedPercentage -= speedPercentStep_;
}

void SpindleConfiguratorService::saveSpeedPercent() {
    spindleController_.setSpeedPercent(
        bufferedPersistentConfig_.speedPercentage
    );

    persistentStorageController_.saveSpindleConfig(
        bufferedPersistentConfig_
    );
}

uint8_t SpindleConfiguratorService::getSpeedPercent() const {
    return bufferedPersistentConfig_.speedPercentage;
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
        rotationTimeStepInMillis_;
}

void SpindleConfiguratorService::decreaseRotationTimeInMillis() {
    bufferedPersistentConfig_.timedRotationInMillis -=
        rotationTimeStepInMillis_;
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
}
