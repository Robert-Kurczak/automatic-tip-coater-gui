#include "Tmc2310StepperDriver.hpp"

#include "application/System/Ports/IGpioPin.hpp"

namespace ATC {
// TODO add SPI config

Tmc2310StepperDriver::Tmc2310StepperDriver(
    Tmc2310StepperDriverPinout& pinout,
    ISpi& spi
) :
    pinout_(pinout),
    spi_(spi) {}

void Tmc2310StepperDriver::init() {
    pinout_.stepPin.init();
    pinout_.stepPin.disable();

    pinout_.directionPin.init(GpioMode::Output, GpioPull::NoPull);
    pinout_.directionPin.setLow();

    pinout_.diagnosticPin.init(GpioMode::Input, GpioPull::PullUp);

    pinout_.chipSelectPin.init(GpioMode::Output, GpioPull::NoPull);
    pinout_.chipSelectPin.setHigh();
}

void Tmc2310StepperDriver::startStepping() {
    pinout_.stepPin.enable();
}

void Tmc2310StepperDriver::stopStepping() {
    pinout_.stepPin.disable();
}

void Tmc2310StepperDriver::setMicrosecondsBetweenStepToggle(
    uint32_t value
) {
    pinout_.stepPin.setToggleMicroseconds(value);
}

void Tmc2310StepperDriver::setDirectionClockwise() {
    pinout_.directionPin.setLow();
}

void Tmc2310StepperDriver::setDirectionCounterClockwise() {
    pinout_.directionPin.setHigh();
}

[[nodiscard]] bool Tmc2310StepperDriver::isFaultDetected() const {
    return pinout_.diagnosticPin.isLow();
}
}