#include "GpioPin.hpp"

#include "main.h"

void GpioPin::setGpioConfig(
    uint32_t mode,
    uint32_t pull,
    uint32_t speed,
    uint32_t alternate
) {
    GPIO_InitTypeDef initStruct {0};
    initStruct.Pin = pin;
    initStruct.Mode = mode;
    initStruct.Pull = pull;
    initStruct.Speed = speed;
    initStruct.Alternate = alternate;
    HAL_GPIO_DeInit(&port, pin);
    HAL_GPIO_Init(&port, &initStruct);
}

GpioPin::GpioPin(GPIO_TypeDef& port_, const uint16_t pin_) :
    port(port_),
    pin(pin_) {}

void GpioPin::setInputMode() {
    setGpioConfig(GPIO_MODE_INPUT, GPIO_NOPULL);
}

void GpioPin::setInputPullUpMode() {
    setGpioConfig(GPIO_MODE_INPUT, GPIO_PULLUP);
}

void GpioPin::setInputPullDownMode() {
    setGpioConfig(GPIO_MODE_INPUT, GPIO_PULLDOWN);
}

bool GpioPin::isHigh() {
    return HAL_GPIO_ReadPin(&port, pin) == GPIO_PIN_SET;
}

void GpioPin::setOutputMode() {
    setGpioConfig(GPIO_MODE_OUTPUT_PP, GPIO_NOPULL);
}

void GpioPin::setHigh() {
    HAL_GPIO_WritePin(&port, pin, GPIO_PIN_SET);
}

void GpioPin::setLow() {
    HAL_GPIO_WritePin(&port, pin, GPIO_PIN_RESET);
}