#include "TargetSystemRoot.hpp"
#include "main.h"
#include "touchgfx/hal/OSWrappers.hpp"

static ATC::TargetSystemRoot& targetSystemRoot =
    ATC::TargetSystemRoot::getSystemRoot();

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
    ATC::SystemInterrupts& interrupts =
        targetSystemRoot.getSystemApi().interrupts;

    if (htim->Instance == TIM3) {
        interrupts.xAxisInterruptService.handleStepInterrupt();
    } else if (htim->Instance == TIM4) {
        interrupts.yAxisInterruptService.handleStepInterrupt();
    } else if (htim->Instance == TIM5) {
        interrupts.zAxisInterruptService.handleStepInterrupt();
    }
}