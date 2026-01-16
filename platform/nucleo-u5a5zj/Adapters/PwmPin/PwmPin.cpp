#include "PwmPin.hpp"

namespace ATC {
PwmPin::PwmPin(TIM_HandleTypeDef& timerHandle, uint32_t channel) :
    timerHandle_(timerHandle),
    channel_(channel) {}

void PwmPin::setDutyCycle(uint8_t percent) {
    const uint32_t autoReloadRegister =
        __HAL_TIM_GET_AUTORELOAD(&timerHandle_);

    const uint32_t dutyCycle = (autoReloadRegister * percent) / 100;

    __HAL_TIM_SET_COMPARE(&timerHandle_, channel_, dutyCycle);
}
}