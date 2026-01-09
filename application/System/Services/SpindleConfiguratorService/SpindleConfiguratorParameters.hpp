#pragma once

#include <cstdint>

namespace ATC {
struct SpindleConfiguratorParameters {
    uint32_t showcaseRotationTimeMillis;
    uint8_t speedPercentStep;
    uint32_t rotationTimeStepMillis;
};
}