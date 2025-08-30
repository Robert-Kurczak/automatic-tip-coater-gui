#pragma once

#include "ISpindleController.hpp"
#include "application/System/Drivers/Logger/ILogger.hpp"
#include "application/System/Drivers/Motor/IMotor.hpp"

#include <stdint.h>

namespace ATC {
class SpindleController : public ISpindleController {
private:
    ILogger& logger_;
    IMotor& motor_;

    uint8_t speedPercent_ = 50;
    uint32_t rotationTimeMillis_ = 3000;

public:
    SpindleController(ILogger& logger, IMotor& motor);

    virtual void tick() override;
    virtual void init() override;

    virtual void startRotation() override;
    virtual void startTimedRotation(uint32_t rotationMillis) override;
    virtual void startTimedRotation() override;

    virtual void stopRotation() override;

    virtual bool isTimedRotationFinished() const override;

    virtual void setDirectionClockwise() override;
    virtual void setDirectionCounterClockwise() override;
    virtual bool isDirectionClockwise() const override;

    virtual void setSpeedPercent(uint8_t value) override;
    virtual uint8_t getSpeedPercent() const override;

    virtual void setRotationTimeMillis(uint32_t value) override;
    virtual uint32_t getRotationTimeMillis() const override;
};
}
