#pragma once

#include <stdint.h>

namespace ATC {
class ISystemClock {
public:
    ISystemClock() = default;
    ISystemClock(const ISystemClock&) = delete;
    ISystemClock& operator=(const ISystemClock&) = delete;
    ISystemClock(ISystemClock&&) = delete;
    ISystemClock& operator=(ISystemClock&&) = delete;
    virtual ~ISystemClock() = default;

    virtual void delayMilliseconds(uint32_t value) = 0;
    [[nodiscard]] virtual uint32_t getMillisecondsSinceStart() = 0;
};
}