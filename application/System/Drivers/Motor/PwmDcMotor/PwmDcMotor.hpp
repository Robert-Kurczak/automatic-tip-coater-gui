#pragma once

#include "../IMotor.hpp"
#include "application/System/Ports/IGpioPin.hpp"
#include "application/System/Ports/IPwmPin.hpp"

namespace ATC {
struct PwmDcMotorPinout {
    // NOLINTBEGIN(cppcoreguidelines-avoid-const-or-ref-data-members)
    IPwmPin& speedPwmPin;
    IGpioPin& directionPin;
    IGpioPin& faultPin;
    // NOLINTEND(cppcoreguidelines-avoid-const-or-ref-data-members)
};

class PwmDcMotor : public IMotor {
private:
    PwmDcMotorPinout& pinout_;

    uint8_t dutyCyclePercent_ = 0;

public:
    PwmDcMotor(PwmDcMotorPinout& pinout);

    void init() override;

    void startRotation(uint8_t speedPercent) override;
    void stopRotation() override;

    void setDirectionClockwise() override;
    void setDirectionCounterClockwise() override;
    [[nodiscard]] bool isDirectionClockwise() const override;

    [[nodiscard]] bool isFaultDetected() override;
};
}