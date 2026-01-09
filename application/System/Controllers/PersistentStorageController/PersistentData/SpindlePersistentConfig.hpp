#pragma once

#include <cstdint>

namespace ATC {
struct SpindlePersistentConfig {
    uint8_t speedPercent;
    bool isDirectionClockwise;
    uint32_t timedRotationInMillis;
};
}