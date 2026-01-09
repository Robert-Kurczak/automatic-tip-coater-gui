#pragma once

#include "../ISwitch.hpp"
#include "application/System/Ports/IGpioPin.hpp"

namespace ATC {
class GpioActiveHighSwitch : public ISwitch {
private:
    IGpioPin& togglePin_;

public:
    GpioActiveHighSwitch(IGpioPin& togglePin);

    void init() override;

    void turnOn() override;
    void turnOff() override;
};
}