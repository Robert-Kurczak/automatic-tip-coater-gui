#pragma once

#include <cstdint>

namespace ATC {
class IPwmPin {
public:
    IPwmPin() = default;
    IPwmPin(const IPwmPin&) = delete;
    IPwmPin& operator=(const IPwmPin&) = delete;
    IPwmPin(IPwmPin&&) = delete;
    IPwmPin& operator=(IPwmPin&&) = delete;
    virtual ~IPwmPin() = default;

    virtual void setDutyCycle(uint8_t percent) = 0;
};
}