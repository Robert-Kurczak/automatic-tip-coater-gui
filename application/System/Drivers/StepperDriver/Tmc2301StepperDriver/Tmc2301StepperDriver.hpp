#pragma once

#include "../IStepperDriver.hpp"
#include "application/System/Ports/IAsyncPulsePin.hpp"
#include "application/System/Ports/IGpioPin.hpp"
#include "application/System/Ports/ISpi.hpp"

namespace ATC {
struct Tmc2301StepperDriverPinout {
    // NOLINTBEGIN(cppcoreguidelines-avoid-const-or-ref-data-members)
    IAsyncPulsePin& stepPin;
    IGpioPin& directionPin;
    IGpioPin& diagnosticPin;
    IGpioPin& chipSelectPin;
    // NOLINTEND(cppcoreguidelines-avoid-const-or-ref-data-members)
};

class Tmc2301StepperDriver : public IStepperDriver {
private:
    Tmc2301StepperDriverPinout& pinout_;
    ISpi& spi_;

public:
    Tmc2301StepperDriver(Tmc2301StepperDriverPinout& pinout, ISpi& spi);

    void init() override;

    void start() override;
    void stop() override;

    void setDirectionClockwise() override;
    void setDirectionCounterClockwise() override;

    [[nodiscard]] bool isFaultDetected() const override;
};
}