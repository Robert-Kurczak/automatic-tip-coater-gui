#pragma once

#include <stdint.h>

namespace ATC {
class ISystemClock {
public:
    virtual ~ISystemClock() = default;

    virtual void delayMilliseconds(const uint32_t value) = 0;
    virtual uint32_t getMillisecondsSinceStart() = 0;
};
}