#pragma once

#include <cstdint>

namespace ATC {
struct AxisConfiguratorParameters {
    uint8_t positionStep;
    uint8_t speedPercentStep;
    uint32_t speedShowcasePosition;
};
}