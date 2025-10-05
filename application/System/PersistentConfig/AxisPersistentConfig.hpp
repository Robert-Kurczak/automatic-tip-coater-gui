#pragma once

#include <stdint.h>

namespace ATC {
struct AxisPersistentConfig {
    uint32_t startPosition;
    uint32_t endPosition;
    uint32_t speed;

    static constexpr AxisPersistentConfig defaultXAxisConfig() {
        return AxisPersistentConfig {
            .startPosition = 100, .endPosition = 1000, .speed = 200
        };
    }

    static constexpr AxisPersistentConfig defaultYAxisConfig() {
        return AxisPersistentConfig {
            .startPosition = 0, .endPosition = 1000, .speed = 200
        };
    }

    static constexpr AxisPersistentConfig defaultZAxisConfig() {
        return AxisPersistentConfig {
            .startPosition = 300, .endPosition = 1000, .speed = 200
        };
    }
};
}