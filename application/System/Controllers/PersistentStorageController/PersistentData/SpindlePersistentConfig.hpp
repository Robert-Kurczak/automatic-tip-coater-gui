#pragma once

#include <cstdint>

namespace ATC {
struct SpindlePersistentConfig {
    uint8_t speedPercentage;
    bool isDirectionClockwise;
    uint32_t timedRotationInMillis;
};
}