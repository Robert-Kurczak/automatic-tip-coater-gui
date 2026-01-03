#include "PwmDcMotor.hpp"

namespace ATC {
PwmDcMotor::PwmDcMotor(PwmDcMotorPinout& pinout) : pinout_(pinout) {}

void PwmDcMotor::init() {
    pinout_.directionPin.setOutputMode();
    pinout_.directionPin.setLow();
}

void PwmDcMotor::startRotation(uint8_t speedPercent) {
    pinout_.speedPwmPin.setDutyCycle(speedPercent);
}

void PwmDcMotor::stopRotation() {
    pinout_.speedPwmPin.setDutyCycle(0);
}

void PwmDcMotor::setDirectionClockwise() {
    pinout_.directionPin.setHigh();
}

void PwmDcMotor::setDirectionCounterClockwise() {
    pinout_.directionPin.setLow();
}

bool PwmDcMotor::isDirectionClockwise() const {
    return pinout_.directionPin.isHigh();
}

bool PwmDcMotor::isFaultDetected() {
    return !pinout_.faultPin.isHigh();
}
}