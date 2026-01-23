#include "TargetSystemRoot.hpp"
#include "main.h"
#include "stm32u5xx_hal_gpio.h"
#include "touchgfx/hal/OSWrappers.hpp"

static ATC::TargetSystemRoot& targetSystemRoot =
    ATC::TargetSystemRoot::getSystemRoot();

static ATC::SystemInterrupts& systemInterrupts =
    targetSystemRoot.getSystemApi().interrupts;

static uint32_t vSyncStart = 0;

void ATC_Init() {
    targetSystemRoot.init();
}

void ATC_Loop() {
    targetSystemRoot.tick();

    const uint32_t currentTime = HAL_GetTick();

    if (currentTime - vSyncStart >= 17) {
        touchgfx::OSWrappers::signalVSync();
        vSyncStart = currentTime;
    }
}

extern "C" void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef* htim) {
    if (htim->Instance == TIM3) {
        systemInterrupts.xAxisInterruptService.handleStepInterrupt();
    } else if (htim->Instance == TIM4) {
        systemInterrupts.yAxisInterruptService.handleStepInterrupt();
    } else if (htim->Instance == TIM5) {
        systemInterrupts.zAxisInterruptService.handleStepInterrupt();
    }
}

extern "C" void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    switch (GPIO_Pin) {
    case xAxis_MIN_LIMIT_Pin:
        systemInterrupts.xAxisInterruptService
            .handleMinLimitReachedInterrupt();
        return;

    case xAxis_MAX_LIMIT_Pin:
        systemInterrupts.xAxisInterruptService
            .handleMaxLimitReachedInterrupt();
        return;

    case yAxis_MIN_LIMIT_Pin:
        systemInterrupts.yAxisInterruptService
            .handleMinLimitReachedInterrupt();
        return;

    case yAxis_MAX_LIMIT_Pin:
        systemInterrupts.yAxisInterruptService
            .handleMaxLimitReachedInterrupt();
        return;

    case zAxis_MIN_LIMIT_Pin:
        systemInterrupts.zAxisInterruptService
            .handleMinLimitReachedInterrupt();
        return;

    case zAxis_MAX_LIMIT_Pin:
        systemInterrupts.zAxisInterruptService
            .handleMaxLimitReachedInterrupt();
        return;

    }
}