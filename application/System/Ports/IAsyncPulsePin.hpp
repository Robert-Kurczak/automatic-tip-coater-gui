#pragma once

#include <cstdint>

namespace ATC {
class IAsyncPulsePin {
public:
    IAsyncPulsePin() = default;
    IAsyncPulsePin(const IAsyncPulsePin&) = delete;
    IAsyncPulsePin& operator=(const IAsyncPulsePin&) = delete;
    IAsyncPulsePin(IAsyncPulsePin&&) = delete;
    IAsyncPulsePin& operator=(IAsyncPulsePin&&) = delete;
    virtual ~IAsyncPulsePin() = default;

    virtual void init() = 0;

    virtual void enable() = 0;
    virtual void disable() = 0;

    virtual void setToggleMicroseconds(uint32_t value) = 0;
};
}