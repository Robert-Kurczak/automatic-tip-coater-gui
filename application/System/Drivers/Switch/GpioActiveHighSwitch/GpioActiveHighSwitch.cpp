#include "GpioActiveHighSwitch.hpp"

#include "application/System/Ports/IGpioPin.hpp"

namespace ATC {
GpioActiveHighSwitch::GpioActiveHighSwitch(IGpioPin& togglePin) :
    togglePin_(togglePin) {}

void GpioActiveHighSwitch::init() {
    togglePin_.init(GpioMode::Output, GpioPull::NoPull);
}

void GpioActiveHighSwitch::turnOn() {
    togglePin_.setHigh();
};

void GpioActiveHighSwitch::turnOff() {
    togglePin_.setHigh();
};
};