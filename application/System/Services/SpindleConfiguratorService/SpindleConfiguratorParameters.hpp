#pragma once

#include <cstdint>

namespace ATC {
struct SpindleConfiguratorParameters {
    uint32_t showcaseRotationTimeInMillis;
    uint8_t speedPercentStep;
    uint32_t rotationTimeStepInMillis;
};
}