#pragma once

#include <stdint.h>

namespace ATC {
struct HeaterPersistentConfig {
    uint16_t targetTemperatureInCelsius;

    static constexpr HeaterPersistentConfig getDefaultConfig() {
        return HeaterPersistentConfig {.targetTemperatureInCelsius = 200};
    }
};
}