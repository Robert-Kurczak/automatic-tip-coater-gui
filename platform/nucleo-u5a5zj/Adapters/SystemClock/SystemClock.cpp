#include "SystemClock.hpp"

#include "main.h"

namespace ATC {
void SystemClock::delayMiliseconds(const uint32_t value) {
    HAL_Delay(value);
}

uint32_t SystemClock::getMillisecondsSinceStart() {
    return HAL_GetTick();
}
}