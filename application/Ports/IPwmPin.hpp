#pragma once

#include <stdint.h>

namespace ATC {
class IPwmPin {
public:
    virtual ~IPwmPin() = default;

    virtual void setDutyCycle(uint8_t percent) = 0;
};
}