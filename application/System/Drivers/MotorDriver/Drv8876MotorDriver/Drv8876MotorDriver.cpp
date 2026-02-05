#include "Drv8876MotorDriver.hpp"

#include "application/System/Ports/IGpioPin.hpp"

namespace ATC {
DRV8876MotorDriver::DRV8876MotorDriver(Drv8876MotorDriverPinout& pinout) :
    pinout_(pinout) {}

void DRV8876MotorDriver::init() {
    pinout_.modePin.init(GpioMode::Output, GpioPull::NoPull);
    pinout_.modePin.setLow();

    pinout_.enablePin.setDutyCycle(0);

    pinout_.phasePin.init(GpioMode::Output, GpioPull::NoPull);
    pinout_.phasePin.setLow();

    pinout_.sleepPin.init(GpioMode::Output, GpioPull::NoPull);
    pinout_.sleepPin.setLow();

    pinout_.faultPin.init(GpioMode::Input, GpioPull::PullUp);
}

void DRV8876MotorDriver::startRotation(uint8_t speedPercent) {
    pinout_.sleepPin.setHigh();
    pinout_.enablePin.setDutyCycle(speedPercent);
}

void DRV8876MotorDriver::stopRotation() {
    pinout_.sleepPin.setLow();
    pinout_.enablePin.setDutyCycle(0);
}

void DRV8876MotorDriver::setDirectionClockwise() {
    pinout_.phasePin.setHigh();
}

void DRV8876MotorDriver::setDirectionCounterClockwise() {
    pinout_.phasePin.setLow();
}

bool DRV8876MotorDriver::isDirectionClockwise() const {
    return pinout_.phasePin.isHigh();
}

bool DRV8876MotorDriver::isFaultDetected() {
    return pinout_.faultPin.isLow();
}
}
