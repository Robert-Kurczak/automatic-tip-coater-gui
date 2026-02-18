#pragma once

#include <cstdint>

namespace ATC {
struct AxisPersistentConfig {
    uint32_t startPositionInMicrometers;
    uint32_t endPositionInMicrometers;
    uint16_t speedInMillimetersPerSecond;

    constexpr bool operator==(const AxisPersistentConfig&) const =
        default;
};
}