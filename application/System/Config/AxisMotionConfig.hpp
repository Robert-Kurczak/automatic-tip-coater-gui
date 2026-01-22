#pragma once

#include "application/System/Controllers/AxisMotionController/AxisMotionParameters.hpp"

namespace ATC {
inline constexpr AxisMotionParameters X_AXIS_MOTION_PARAMETERS {
    .millimetersPerRotation = 8,
    .motorStepsPerRotation = 200,
    .driverStepDivider = 16,
    .isClockwiseRotationForwardMovement = false,
    .stepErrorMargin = 5
};

inline constexpr AxisMotionParameters Y_AXIS_MOTION_PARAMETERS {
    .millimetersPerRotation = 8,
    .motorStepsPerRotation = 200,
    .driverStepDivider = 16,
    .isClockwiseRotationForwardMovement = true,
    .stepErrorMargin = 1
};
}