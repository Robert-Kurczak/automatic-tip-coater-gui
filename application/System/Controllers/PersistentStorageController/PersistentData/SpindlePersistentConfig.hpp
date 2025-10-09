#pragma once

#include <stdint.h>

namespace ATC {
struct SpindlePersistentConfig {
    uint8_t speedPercentage;
    bool isDirectionClockwise;
    uint32_t timedRotationInMillis;

    static constexpr SpindlePersistentConfig getDefaultConfig() {
        return SpindlePersistentConfig {
            .speedPercentage = 80,
            .isDirectionClockwise = true,
            .timedRotationInMillis = 3000
        };
    }
};
}