#pragma once

#include <cstdint>

namespace ATC {
struct AxisMotionParameters {
    uint8_t millimetersPerRotation;
    uint16_t motorStepsPerRotation;
    uint8_t driverStepDivider;
    bool isClockwiseRotationForwardMovement;
    uint8_t stepErrorMargin;
};
}