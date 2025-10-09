#pragma once

#include <stdint.h>

namespace ATC {
struct AxisPersistentConfig {
    uint32_t startPosition;
    uint32_t endPosition;
    uint32_t speed;

    static constexpr AxisPersistentConfig getDefaultXAxisConfig() {
        return AxisPersistentConfig {
            .startPosition = 100, .endPosition = 1000, .speed = 200
        };
    }

    static constexpr AxisPersistentConfig getDefaultYAxisConfig() {
        return AxisPersistentConfig {
            .startPosition = 100, .endPosition = 1000, .speed = 200
        };
    }

    static constexpr AxisPersistentConfig getDefaultZAxisConfig() {
        return AxisPersistentConfig {
            .startPosition = 100, .endPosition = 1000, .speed = 200
        };
    }
};
}