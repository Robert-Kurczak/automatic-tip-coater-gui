#pragma once

#include <cstdint>

namespace ATC {
struct AxisConfiguratorParameters {
    uint8_t positionStep;
    uint8_t speedStep;
    uint32_t speedShowcasePosition;
};
}