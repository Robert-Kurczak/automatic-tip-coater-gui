#pragma once

#include "ISpindleConfiguratorService.hpp"
#include "application/System/Controllers/SpindleController/ISpindleController.hpp"
#include "application/System/Drivers/Logger/ILogger.hpp"

namespace ATC {
class SpindleConfiguratorService : public ISpindleConfiguratorService {
private:
    ILogger& logger_;
    ISpindleController& spindleController_;
    const uint32_t showcaseRotationTimeInMillis_;
    const uint8_t speedPercentStep_;
    const uint32_t rotationTimeStepInMillis_;

public:
    SpindleConfiguratorService(
        ILogger& logger,
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
