#pragma once

#include <stdint.h>

namespace ATC {
struct HeaterPersistentConfig {
    uint16_t targetTemperatureInCelsius;
};
}