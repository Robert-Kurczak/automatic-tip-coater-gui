#include "SpindleConfiguratorService.hpp"

namespace ATC {
SpindleConfiguratorService::SpindleConfiguratorService(
    IPersistentStorageController& persistentStorageController,
    ISpindleController& spindleController
) :
    persistentStorageController_(persistentStorageController),
    spindleController_(spindleController) {}

void SpindleConfiguratorService::resetBufferedConfig() {
    bufferedPersistentConfig_.speedPercentage =
        spindleController_.getSpeedPercent();

    bufferedPersistentConfig_.isDirectionClockwise =
        spindleController_.isDirectionClockwise();

    bufferedPersistentConfig_.timedRotationInMillis =
        spindleController_.getRotationTimeInMillis();
}

void SpindleConfiguratorService::showcaseRotation() {
    spindleController_.startTimedRotation(SHOWCASE_ROTATION_TIME_MILLIS_);
}

void SpindleConfiguratorService::increaseSpeedPercent() {
    bufferedPersistentConfig_.speedPercentage += SPEED_PERCENT_STEP_;
}

void SpindleConfiguratorService::decreaseSpeedPercent() {
    bufferedPersistentConfig_.speedPercentage -= SPEED_PERCENT_STEP_;
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
        ROTATION_TIME_STEP_MILLIS_;
}

void SpindleConfiguratorService::decreaseRotationTimeInMillis() {
    bufferedPersistentConfig_.timedRotationInMillis -=
        ROTATION_TIME_STEP_MILLIS_;
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
