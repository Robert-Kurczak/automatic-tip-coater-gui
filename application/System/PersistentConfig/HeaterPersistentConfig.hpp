#pragma once

#include <stdint.h>

namespace ATC {
struct HeaterPersistentConfig {
    uint16_t targetTemperatureInCelsius;

    static constexpr HeaterPersistentConfig defaultConfig() {
        return HeaterPersistentConfig {.targetTemperatureInCelsius = 200};
    }
};
}