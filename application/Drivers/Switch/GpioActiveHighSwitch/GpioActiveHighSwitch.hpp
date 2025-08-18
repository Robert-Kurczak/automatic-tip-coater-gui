#pragma once

#include "../ISwitch.hpp"
#include "application/Ports/IGpioPin.hpp"

namespace ATC {
class GpioActiveHighSwitch : public ISwitch {
private:
    IGpioPin& togglePin_;

public:
    GpioActiveHighSwitch(IGpioPin& togglePin);

    virtual void init() override;

    virtual void turnOn() override;
    virtual void turnOff() override;
};
}