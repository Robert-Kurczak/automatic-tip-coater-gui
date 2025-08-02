#include "DelayProvider.hpp"

#include "main.h"

namespace ATC {
void DelayProvider::delayMiliseconds(const uint32_t value) {
    HAL_Delay(value);
}
}