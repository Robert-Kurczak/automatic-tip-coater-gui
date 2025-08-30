#include "TargetSystemRoot.hpp"
#include "main.h"
#include "touchgfx/hal/OSWrappers.hpp"

static ATC::TargetSystemRoot targetSystemRoot =
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
