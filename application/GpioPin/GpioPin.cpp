#include "GpioPin.hpp"

#include "main.h"

void GpioPin::setGpioConfig(
    uint32_t mode,
    uint32_t pull,
    uint32_t speed,
    uint32_t alternate
) {
    GPIO_InitTypeDef initStruct {0};
    initStruct.Pin = pin_;
    initStruct.Mode = mode;
    initStruct.Pull = pull;
    initStruct.Speed = speed;
    initStruct.Alternate = alternate;
    HAL_GPIO_DeInit(&port_, pin_);
    HAL_GPIO_Init(&port_, &initStruct);
}

GpioPin::GpioPin(GPIO_TypeDef& port, const uint16_t pin) :
    port_(port),
    pin_(pin) {}

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
    return HAL_GPIO_ReadPin(&port_, pin_) == GPIO_PIN_SET;
}

void GpioPin::setOutputMode() {
    setGpioConfig(GPIO_MODE_OUTPUT_PP, GPIO_NOPULL);
}

void GpioPin::setHigh() {
    HAL_GPIO_WritePin(&port_, pin_, GPIO_PIN_SET);
}

void GpioPin::setLow() {
    HAL_GPIO_WritePin(&port_, pin_, GPIO_PIN_RESET);
}