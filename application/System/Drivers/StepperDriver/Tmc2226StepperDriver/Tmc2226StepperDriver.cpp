#include "Tmc2226StepperDriver.hpp"

#include "application/System/Ports/IGpioPin.hpp"

namespace ATC {
Tmc2226StepperDriver::Tmc2226StepperDriver(
    Tmc2226StepperDriverPinout& pinout
) :
    pinout_(pinout) {}

void Tmc2226StepperDriver::init() {
    pinout_.stepPin.init();
    pinout_.stepPin.disable();

    pinout_.directionPin.init(GpioMode::Output, GpioPull::NoPull);
    pinout_.directionPin.setLow();

    pinout_.diagnosticPin.init(GpioMode::Input, GpioPull::PullUp);
}

void Tmc2226StepperDriver::startStepping() {
    pinout_.stepPin.enable();
}

void Tmc2226StepperDriver::stopStepping() {
    pinout_.stepPin.disable();
}

void Tmc2226StepperDriver::setMicrosecondsBetweenStepToggle(
    uint32_t value
) {
    pinout_.stepPin.setToggleMicroseconds(value);
}

void Tmc2226StepperDriver::setDirectionClockwise() {
    pinout_.directionPin.setLow();
}

void Tmc2226StepperDriver::setDirectionCounterClockwise() {
    pinout_.directionPin.setHigh();
}

[[nodiscard]] bool Tmc2226StepperDriver::isFaultDetected() const {
    return pinout_.diagnosticPin.isLow();
}
}