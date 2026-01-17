#include "Tmc2301StepperDriver.hpp"

namespace ATC {
// TODO add SPI config

Tmc2301StepperDriver::Tmc2301StepperDriver(
    Tmc2301StepperDriverPinout& pinout,
    ISpi& spi
) :
    pinout_(pinout),
    spi_(spi) {}

void Tmc2301StepperDriver::init() {
    pinout_.stepPin.disable();

    pinout_.directionPin.setOutputMode();
    pinout_.directionPin.setLow();

    pinout_.diagnosticPin.setInputPullUpMode();

    pinout_.chipSelectPin.setOutputMode();
    pinout_.chipSelectPin.setHigh();
}

void Tmc2301StepperDriver::start() {
    pinout_.stepPin.enable();
}

void Tmc2301StepperDriver::stop() {
    pinout_.stepPin.disable();
}

void Tmc2301StepperDriver::setDirectionClockwise() {
    pinout_.directionPin.setLow();
}

void Tmc2301StepperDriver::setDirectionCounterClockwise() {
    pinout_.directionPin.setHigh();
}

[[nodiscard]] bool Tmc2301StepperDriver::isFaultDetected() const {
    return !pinout_.diagnosticPin.isHigh();
}
}