#pragma once

#include "../IStepperDriver.hpp"
#include "application/System/Ports/IAsyncPulsePin.hpp"
#include "application/System/Ports/IGpioPin.hpp"
#include "application/System/Ports/ISpi.hpp"

namespace ATC {
struct Tmc2310StepperDriverPinout {
    // NOLINTBEGIN(cppcoreguidelines-avoid-const-or-ref-data-members)
    IAsyncPulsePin& stepPin;
    IGpioPin& directionPin;
    IGpioPin& diagnosticPin;
    IGpioPin& chipSelectPin;
    // NOLINTEND(cppcoreguidelines-avoid-const-or-ref-data-members)
};

class Tmc2310StepperDriver : public IStepperDriver {
private:
    Tmc2310StepperDriverPinout& pinout_;
    ISpi& spi_;

public:
    Tmc2310StepperDriver(Tmc2310StepperDriverPinout& pinout, ISpi& spi);

    void init() override;

    void startStepping() override;
    void stopStepping() override;

    void setMicrosecondsBetweenStepToggle(uint32_t value) override;

    void setDirectionClockwise() override;
    void setDirectionCounterClockwise() override;

    [[nodiscard]] bool isFaultDetected() const override;
};
}