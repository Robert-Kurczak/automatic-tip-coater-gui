#pragma once

// TODO abstract it out of application code
// This should be an adapter to IGpioPin interface
#include <stdint.h>
#include <stm32u5a5xx.h>

class GpioPin {
private:
    GPIO_TypeDef& port;
    const uint16_t pin;

    void setGpioConfig(
        uint32_t mode = 0,
        uint32_t pull = 0,
        uint32_t speed = 0,
        uint32_t alternate = 0
    );

public:
    GpioPin(GPIO_TypeDef& port_, const uint16_t pin_);

    void setInputMode();
    void setInputPullUpMode();
    void setInputPullDownMode();
    bool isHigh();

    void setOutputMode();
    void setHigh();
    void setLow();
};