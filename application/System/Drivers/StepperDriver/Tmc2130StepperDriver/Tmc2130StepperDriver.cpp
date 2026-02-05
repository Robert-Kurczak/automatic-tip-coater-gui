#include "Tmc2130StepperDriver.hpp"

#include "application/System/Ports/IGpioPin.hpp"

namespace ATC {
// TODO add SPI config

Tmc2130StepperDriver::Tmc2130StepperDriver(
    Tmc2130StepperDriverPinout& pinout,
    ISpi& spi
) :
    pinout_(pinout),
    spi_(spi) {}

void Tmc2130StepperDriver::init() {
    pinout_.stepPin.init();
    pinout_.stepPin.disable();

    pinout_.directionPin.init(GpioMode::Output, GpioPull::NoPull);
    pinout_.directionPin.setLow();

    pinout_.diagnosticPin.init(GpioMode::Input, GpioPull::PullUp);

    pinout_.chipSelectPin.init(GpioMode::Output, GpioPull::NoPull);
    pinout_.chipSelectPin.setHigh();
}

void Tmc2130StepperDriver::startStepping() {
    pinout_.stepPin.enable();
}

void Tmc2130StepperDriver::stopStepping() {
    pinout_.stepPin.disable();
}

void Tmc2130StepperDriver::setMicrosecondsBetweenStepToggle(
    uint32_t value
) {
    pinout_.stepPin.setToggleMicroseconds(value);
}

void Tmc2130StepperDriver::setDirectionClockwise() {
    pinout_.directionPin.setLow();
}

void Tmc2130StepperDriver::setDirectionCounterClockwise() {
    pinout_.directionPin.setHigh();
}

[[nodiscard]] bool Tmc2130StepperDriver::isFaultDetected() const {
    return pinout_.diagnosticPin.isLow();
}
}