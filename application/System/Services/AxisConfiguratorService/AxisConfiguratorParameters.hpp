#pragma once

#include <cstdint>

namespace ATC {
struct AxisConfiguratorParameters {
    uint32_t positionStepInMicrometers;
    uint8_t speedStepInMillimetersPerSecond;
    uint32_t speedShowcasePositionInMicrometers;
    uint32_t minPositionInMicrometers;
    uint32_t maxPositionInMicrometers;
    uint16_t minSpeedInMillimetersPerSecond;
    uint16_t maxSpeedInMillimetersPerSecond;
};
}