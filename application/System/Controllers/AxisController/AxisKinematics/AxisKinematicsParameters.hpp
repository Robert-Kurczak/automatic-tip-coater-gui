#pragma once

#include <cstdint>

namespace ATC {
struct AxisKinematicsParameters {
    uint8_t millimetersPerRotation;
    uint32_t motorStepsPerRotation;
    uint16_t driverStepDivider;
};
}