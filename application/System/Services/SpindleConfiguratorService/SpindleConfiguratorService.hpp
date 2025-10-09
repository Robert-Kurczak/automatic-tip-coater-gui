#pragma once

#include "ISpindleConfiguratorService.hpp"
#include "application/System/Controllers/PersistentStorageController/IPersistentStorageController.hpp"
#include "application/System/Controllers/PersistentStorageController/PersistentData/SpindlePersistentConfig.hpp"
#include "application/System/Controllers/SpindleController/ISpindleController.hpp"

namespace ATC {
class SpindleConfiguratorService : public ISpindleConfiguratorService {
private:
    IPersistentStorageController& persistentStorageController_;
    ISpindleController& spindleController_;

    const uint32_t showcaseRotationTimeInMillis_;
    const uint8_t speedPercentStep_;
    const uint32_t rotationTimeStepInMillis_;

    SpindlePersistentConfig bufferedPersistentConfig_ {
        .speedPercentage = 0,
        .isDirectionClockwise = false,
        .timedRotationInMillis = 0
    };

public:
    SpindleConfiguratorService(
        IPersistentStorageController& persistentStorageController,
        ISpindleController& spindleController,
        uint32_t showcaseRotationTimeInMillis,
        uint8_t speedPercentStep,
        uint32_t rotationTimeStepInMillis
    );

    virtual void resetBufferedConfig() override;

    virtual void showcaseRotation() override;

    virtual void increaseSpeedPercent() override;
    virtual void decreaseSpeedPercent() override;
    virtual void saveSpeedPercent() override;
    virtual uint8_t getSpeedPercent() const override;

    virtual void setDirectionClockwise() override;
    virtual void setDirectionCounterClockwise() override;
    virtual void saveDirection() override;
    virtual bool isDirectionClockwise() const override;

    virtual void increaseRotationTimeInMillis() override;
    virtual void decreaseRotationTimeInMillis() override;
    virtual void saveRotationTimeInMillis() override;
    virtual uint32_t getRotationTimeInMillis() const override;
};
}
