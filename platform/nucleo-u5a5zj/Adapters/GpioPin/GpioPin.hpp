#pragma once

#include "application/Ports/IGpioPin.hpp"

#include <stdint.h>
#include <stm32u5a5xx.h>

namespace ATC {
class GpioPin : public IGpioPin {
private:
    GPIO_TypeDef& port_;
    const uint16_t pin_;

    void setGpioConfig(
        uint32_t mode = 0,
        uint32_t pull = 0,
        uint32_t speed = 0,
        uint32_t alternate = 0
    );

public:
    GpioPin(GPIO_TypeDef& port, const uint16_t pin);

    virtual void setInputMode() override;
    virtual void setInputPullUpMode() override;
    virtual void setInputPullDownMode() override;
    virtual bool isHigh() override;

    virtual void setOutputMode() override;
    virtual void setHigh() override;
    virtual void setLow() override;
};
}