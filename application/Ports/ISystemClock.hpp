#pragma once

#include <stdint.h>

namespace ATC {
class ISystemClock {
public:
    virtual void delayMiliseconds(const uint32_t value) = 0;
    virtual uint32_t getMillisecondsSinceStart() = 0;
};
}