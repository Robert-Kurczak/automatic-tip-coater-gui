#pragma once

#include <cstdint>

namespace ATC {
struct SpindlePersistentConfig {
    uint8_t speedPercent;
    bool isDirectionClockwise;
    uint32_t timedRotationInMillis;

    constexpr bool operator==(const SpindlePersistentConfig&) const =
        default;
};
}