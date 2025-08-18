#include "GpioActiveHighSwitch.hpp"

namespace ATC {
GpioActiveHighSwitch::GpioActiveHighSwitch(IGpioPin& togglePin) :
    togglePin_(togglePin) {}

void GpioActiveHighSwitch::init() {
    togglePin_.setOutputMode();
}

void GpioActiveHighSwitch::turnOn() {
    togglePin_.setHigh();
};

void GpioActiveHighSwitch::turnOff() {
    togglePin_.setHigh();
};
};