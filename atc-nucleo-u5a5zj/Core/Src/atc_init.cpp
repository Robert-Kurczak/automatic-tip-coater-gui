#include "main.h"
#include "touchgfx/hal/OSWrappers.hpp"

void ATC_Init() {}

void ATC_Loop() {
    touchgfx::OSWrappers::signalVSync();
}
