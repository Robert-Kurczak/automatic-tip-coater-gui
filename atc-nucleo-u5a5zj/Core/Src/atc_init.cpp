#include "main.h"
#include "touchgfx/hal/OSWrappers.hpp"

void ATC_Init() {}


static uint32_t vSyncStart = 0;
void ATC_Loop() {
    const uint32_t currentTime = HAL_GetTick();

    if(currentTime - vSyncStart >= 17) {
        touchgfx::OSWrappers::signalVSync();
        vSyncStart = currentTime;
    }
}
