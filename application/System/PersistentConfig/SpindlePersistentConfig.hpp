#pragma once

#include <stdint.h>

namespace ATC {
struct SpindlePersistentConfig {
    uint8_t spindleSpeedPercentage;
    bool isSpindleDirectionClockwise;
    uint32_t timedRotationInMillis;

    static constexpr SpindlePersistentConfig defaultConfig() {
        return SpindlePersistentConfig {
            .spindleSpeedPercentage = 80,
            .isSpindleDirectionClockwise = true,
            .timedRotationInMillis = 3000
        };
    }
};
}