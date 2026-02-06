#pragma once

#include "../IStepperDriver.hpp"
#include "application/System/Ports/IAsyncPulsePin.hpp"
#include "application/System/Ports/IGpioPin.hpp"

namespace ATC {
struct Tmc2226StepperDriverPinout {
    // NOLINTBEGIN(cppcoreguidelines-avoid-const-or-ref-data-members)
    IAsyncPulsePin& stepPin;
    IGpioPin& directionPin;
    IGpioPin& diagnosticPin;
    // NOLINTEND(cppcoreguidelines-avoid-const-or-ref-data-members)
};

class Tmc2226StepperDriver : public IStepperDriver {
private:
    Tmc2226StepperDriverPinout& pinout_;

public:
    Tmc2226StepperDriver(Tmc2226StepperDriverPinout& pinout);

    void init() override;

    void startStepping() override;
    void stopStepping() override;

    void setMicrosecondsBetweenStepToggle(uint32_t value) override;

    void setDirectionClockwise() override;
    void setDirectionCounterClockwise() override;

    [[nodiscard]] bool isFaultDetected() const override;
};
}