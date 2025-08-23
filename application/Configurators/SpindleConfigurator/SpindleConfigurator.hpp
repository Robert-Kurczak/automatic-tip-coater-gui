#pragma once

#include "ISpindleConfigurator.hpp"
#include "application/Controllers/SpindleController/ISpindleController.hpp"
#include "application/System/Logger/ILogger.hpp"

namespace ATC {
class SpindleConfigurator : public ISpindleConfigurator {
private:
    ILogger& logger_;
    ISpindleController& spindleController_;
    const uint8_t showcaseRotationTimeMillis_;
    const uint8_t speedPercentStep_;
    const uint8_t rotationTimeStep_;

public:
    SpindleConfigurator(
        ILogger& logger,
        ISpindleController& spindleController,
        uint8_t showcaseRotationTimeMillis,
        uint8_t speedPercentStep,
        uint8_t rotationTimeStep
    );

    virtual void showcaseRotation() override;

    virtual void increaseSpeedPercent() override;
    virtual void decreaseSpeedPercent() override;
    virtual void saveSpeedPercent() override;
    virtual uint8_t getSpeedPercent() const override;

    virtual void setDirectionClockwise() override;
    virtual void setDirectionCounterClockwise() override;
    virtual void saveDirection() override;
    virtual bool isDirectionClockwise() const override;

    virtual void increaseRotationTime() override;
    virtual void decreaseRotationTime() override;
    virtual void saveRotationTime() override;
    virtual uint32_t getRotationTimeMillis() const override;
};
}