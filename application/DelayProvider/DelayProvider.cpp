#include "DelayProvider.hpp"

// TODO remove this dependency
#include "../../atc-nucleo-u5a5zj/Core/Inc/main.h"

void DelayProvider::delayMiliseconds(const uint32_t value) {
    // TODO abstract it out
    HAL_Delay(value);
}