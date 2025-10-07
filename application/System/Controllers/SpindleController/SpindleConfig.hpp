#pragma once

#include <stdint.h>

namespace ATC {
struct SpindleConfig {
    uint8_t spindleSpeedPercentage;
    bool isSpindleDirectionClockwise;
    uint32_t timedRotationInMillis;
};
}