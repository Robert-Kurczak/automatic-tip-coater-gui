#include "DelayProvider.hpp"

#include <stdint.h>

// TODO remove this dependency
#include "../../atc-nucleo-u5a5zj/Core/Inc/main.h"

namespace ATC {
void DelayProvider::delayMiliseconds(const uint32_t value) {
    // TODO abstract it out
    HAL_Delay(value);
}
}