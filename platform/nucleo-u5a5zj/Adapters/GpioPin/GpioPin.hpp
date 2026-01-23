#pragma once

#include "application/System/Ports/IGpioPin.hpp"

#include <stdint.h>
#include <stm32u5a5xx.h>

namespace ATC {
class GpioPin : public IGpioPin {
private:
    GPIO_TypeDef& port_;
    const uint16_t pin_;

    void setGpioConfig(
        uint32_t mode,
        uint32_t pull,
        uint32_t speed,
        uint32_t alternate
    );

public:
    GpioPin(GPIO_TypeDef& port, uint16_t pin);

    void init(GpioMode gpioMode, GpioPull gpioPull) override;

    void setHigh() override;
    void setLow() override;
    void toggle() override;

    [[nodiscard]] bool isHigh() const override;
    [[nodiscard]] bool isLow() const override;
};
}
