#pragma once

#include "application/System/Controllers/AxisMotionController/AxisMotionParameters.hpp"

namespace ATC {
inline constexpr AxisMotionParameters MIN_AXIS_MOTION_PARAMETERS {
    .millimetersPerRotation = 1,
    .motorStepsPerRotation = 1,
    .driverStepDivider = 1,
    .isClockwiseRotationForwardMovement = false,
    .stepErrorMargin = 0
};

inline constexpr AxisMotionParameters MAX_AXIS_MOTION_PARAMETERS {
    .millimetersPerRotation = 255,
    .motorStepsPerRotation = 1000,
    .driverStepDivider = 255,
    .isClockwiseRotationForwardMovement = true,
    .stepErrorMargin = 255
};

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

inline constexpr AxisMotionParameters Z_AXIS_MOTION_PARAMETERS {
    .millimetersPerRotation = 8,
    .motorStepsPerRotation = 200,
    .driverStepDivider = 16,
    .isClockwiseRotationForwardMovement = false,
    .stepErrorMargin = 5
};
}