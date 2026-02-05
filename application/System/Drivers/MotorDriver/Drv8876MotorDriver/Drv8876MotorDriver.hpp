#pragma once

#include "../IMotorDriver.hpp"
#include "application/System/Ports/IGpioPin.hpp"
#include "application/System/Ports/IPwmPin.hpp"

namespace ATC {
struct Drv8876MotorDriverPinout {
    // NOLINTBEGIN(cppcoreguidelines-avoid-const-or-ref-data-members)
    IGpioPin& modePin;
    IPwmPin& enablePin;
    IGpioPin& phasePin;
    IGpioPin& sleepPin;
    IGpioPin& faultPin;
    // NOLINTEND(cppcoreguidelines-avoid-const-or-ref-data-members)
};

class DRV8876MotorDriver : public IMotorDriver {
private:
    Drv8876MotorDriverPinout& pinout_;

public:
    DRV8876MotorDriver(Drv8876MotorDriverPinout& pinout);

    void init() override;

    void startRotation(uint8_t speedPercent) override;
    void stopRotation() override;

    void setDirectionClockwise() override;
    void setDirectionCounterClockwise() override;
    [[nodiscard]] bool isDirectionClockwise() const override;

    [[nodiscard]] bool isFaultDetected() override;
};
}