#include "GpioPin.hpp"

#include "application/System/Ports/IGpioPin.hpp"
#include "main.h"
#include "stm32u5xx_hal_gpio.h"

namespace ATC {
constexpr uint32_t convertGpioMode(GpioMode gpioMode) {
    switch (gpioMode) {
    case GpioMode::Input:
        return GPIO_MODE_INPUT;

    case GpioMode::InterruptOnFallingEdge:
        return GPIO_MODE_IT_FALLING;

    case GpioMode::InterruptOnRisingEdge:
        return GPIO_MODE_IT_RISING;

    case GpioMode::InterruptOnAnyEdge:
        return GPIO_MODE_IT_RISING_FALLING;

    case GpioMode::Output:
        return GPIO_MODE_OUTPUT_PP;
    }

    return GPIO_MODE_OUTPUT_PP;
}

constexpr uint32_t convertGpioPull(GpioPull gpioPull) {
    switch (gpioPull) {
    case GpioPull::NoPull:
        return GPIO_NOPULL;
    case GpioPull::PullUp:
        return GPIO_PULLUP;
    case GpioPull::PullDown:
        return GPIO_PULLDOWN;
    }

    return GPIO_NOPULL;
}

GpioPin::GpioPin(GPIO_TypeDef& port, const uint16_t pin) :
    port_(port),
    pin_(pin) {}

void GpioPin::init(GpioMode gpioMode, GpioPull gpioPull) {
    GPIO_InitTypeDef initStruct {0};
    initStruct.Pin = pin_;
    initStruct.Mode = convertGpioMode(gpioMode);
    initStruct.Pull = convertGpioPull(gpioPull);
    initStruct.Speed = GPIO_SPEED_FREQ_LOW;
    initStruct.Alternate = 0;
    HAL_GPIO_DeInit(&port_, pin_);
    HAL_GPIO_Init(&port_, &initStruct);
}

void GpioPin::setHigh() {
    HAL_GPIO_WritePin(&port_, pin_, GPIO_PIN_SET);
}

void GpioPin::setLow() {
    HAL_GPIO_WritePin(&port_, pin_, GPIO_PIN_SET);
}

void GpioPin::toggle() {
    HAL_GPIO_TogglePin(&port_, pin_);
}

[[nodiscard]] bool GpioPin::isHigh() const {
    return HAL_GPIO_ReadPin(&port_, pin_) == GPIO_PIN_SET;
}

[[nodiscard]] bool GpioPin::isLow() const {
    return HAL_GPIO_ReadPin(&port_, pin_) == GPIO_PIN_RESET;
}
}
