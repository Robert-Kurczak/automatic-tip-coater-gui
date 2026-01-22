#pragma once

#include <cstdint>

namespace ATC {
struct AxisPersistentConfig {
    uint32_t startPosition;
    uint32_t endPosition;
    uint32_t speedInMillimetersPerSecond;
};
}