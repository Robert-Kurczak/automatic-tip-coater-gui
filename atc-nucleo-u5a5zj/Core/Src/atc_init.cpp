#include "TargetBoard.hpp"
#include "main.h"
#include "touchgfx/hal/OSWrappers.hpp"

static ATC::TargetBoard targetBoard_ = ATC::TargetBoard::getBoard();
static uint32_t vSyncStart = 0;

void ATC_Init() {
    targetBoard_.init();
}

void ATC_Loop() {
    targetBoard_.tick();

    const uint32_t currentTime = HAL_GetTick();

    if (currentTime - vSyncStart >= 17) {
        touchgfx::OSWrappers::signalVSync();
        vSyncStart = currentTime;
    }
}
