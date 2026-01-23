#pragma once

#include <cstdint>

namespace ATC {
enum class GpioMode : uint8_t {
    Input,
    InterruptOnFallingEdge,
    InterruptOnRisingEdge,
    InterruptOnAnyEdge,
    Output
};

enum class GpioPull : uint8_t { NoPull, PullUp, PullDown };

class IGpioPin {
public:
    IGpioPin() = default;
    IGpioPin(const IGpioPin&) = delete;
    IGpioPin& operator=(const IGpioPin&) = delete;
    IGpioPin(IGpioPin&&) = delete;
    IGpioPin& operator=(IGpioPin&&) = delete;
    virtual ~IGpioPin() = default;

    virtual void init(GpioMode gpioMode, GpioPull gpioPull) = 0;

    virtual void setHigh() = 0;
    virtual void setLow() = 0;
    virtual void toggle() = 0;

    [[nodiscard]] virtual bool isHigh() const = 0;
    [[nodiscard]] virtual bool isLow() const = 0;
};
}