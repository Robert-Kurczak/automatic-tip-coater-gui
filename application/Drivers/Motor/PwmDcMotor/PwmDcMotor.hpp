#pragma once

#include "../IMotor.hpp"
#include "application/Ports/IGpioPin.hpp"
#include "application/Ports/IPwmPin.hpp"

namespace ATC {
struct PwmDcMotorPinout {
    IPwmPin& speedPwmPin;
    IGpioPin& directionPin;
};

class PwmDcMotor : public IMotor {
private:
    PwmDcMotorPinout& pinout_;

    uint8_t dutyCyclePercent_ = 50;

public:
    PwmDcMotor(PwmDcMotorPinout& pinout);

    virtual void init() override;

    virtual void startRotation(uint8_t speedPercent) override;
    virtual void stopRotation() override;

    virtual void setDirectionClockwise() override;
    virtual void setDirectionCounterClockwise() override;
    virtual bool isDirectionClockwise() const override;
};
}