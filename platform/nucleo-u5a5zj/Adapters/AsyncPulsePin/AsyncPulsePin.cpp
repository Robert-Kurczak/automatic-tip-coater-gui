#include "AsyncPulsePin.hpp"

#include "stm32u5xx_hal_def.h"

namespace ATC {
AsyncPulsePin::AsyncPulsePin(
    TIM_HandleTypeDef& timerHandle1MHz,
    uint32_t channel
) :
    timerHandle1MHz_(timerHandle1MHz),
    channel_(channel) {}

void AsyncPulsePin::init() {
    if (HAL_TIM_Base_Start_IT(&timerHandle1MHz_) != HAL_OK) {
        Error_Handler();
    }
}

void AsyncPulsePin::enable() {
    __HAL_TIM_ENABLE(&timerHandle1MHz_);
    __HAL_TIM_SET_COUNTER(&timerHandle1MHz_, 0);
};

void AsyncPulsePin::disable() {
    __HAL_TIM_DISABLE(&timerHandle1MHz_);
};

void AsyncPulsePin::setToggleMicroseconds(uint32_t value) {
    __HAL_TIM_SET_AUTORELOAD(&timerHandle1MHz_, value);
    __HAL_TIM_SET_COMPARE(&timerHandle1MHz_, channel_, value);
};
}