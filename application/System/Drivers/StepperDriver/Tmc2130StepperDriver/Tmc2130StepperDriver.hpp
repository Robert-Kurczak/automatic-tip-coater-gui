#pragma once

#include "../IStepperDriver.hpp"
#include "application/System/Ports/IAsyncPulsePin.hpp"
#include "application/System/Ports/IGpioPin.hpp"
#include "application/System/Ports/ISpi.hpp"

namespace ATC {
struct Tmc2130StepperDriverPinout {
    // NOLINTBEGIN(cppcoreguidelines-avoid-const-or-ref-data-members)
    IAsyncPulsePin& stepPin;
    IGpioPin& directionPin;
    IGpioPin& diagnosticPin;
    IGpioPin& chipSelectPin;
    // NOLINTEND(cppcoreguidelines-avoid-const-or-ref-data-members)
};

class Tmc2130StepperDriver : public IStepperDriver {
private:
    Tmc2130StepperDriverPinout& pinout_;
    ISpi& spi_;

public:
    Tmc2130StepperDriver(Tmc2130StepperDriverPinout& pinout, ISpi& spi);

    void init() override;

    void startStepping() override;
    void stopStepping() override;

    void setMicrosecondsBetweenStepToggle(uint32_t value) override;

    void setDirectionClockwise() override;
    void setDirectionCounterClockwise() override;

    [[nodiscard]] bool isFaultDetected() const override;
};
}