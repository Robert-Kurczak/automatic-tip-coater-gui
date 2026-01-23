#pragma once

#include "../IOutputSwitch.hpp"
#include "application/System/Drivers/Common/ActiveLevel.hpp"
#include "application/System/Ports/IGpioPin.hpp"

namespace ATC {
template<ActiveLevel LEVEL>
class GpioOutputSwitch : public IOutputSwitch {
private:
    IGpioPin& togglePin_;

public:
    GpioOutputSwitch(IGpioPin& togglePin) : togglePin_(togglePin) {}

    void init() override {
        togglePin_.init(GpioMode::Output, GpioPull::NoPull);
    }

    void turnOn() override {
        if constexpr (LEVEL == ActiveLevel::ActiveHigh) {
            togglePin_.setHigh();
        } else {
            togglePin_.setLow();
        }
    }

    void turnOff() override {
        if constexpr (LEVEL == ActiveLevel::ActiveHigh) {
            togglePin_.setLow();
        } else {
            togglePin_.setHigh();
        }
    }
};
}