#include "application/System/Config/ComponentConfig/AxisMotionConfig.hpp"
#include "application/System/Controllers/AxisMotionController/AxisMotionParameters.hpp"

namespace ATC {
template<AxisMotionParameters MotionParameters>
struct AxisMotionConfigValidator {
    static_assert(
        MotionParameters.millimetersPerRotation >=
        MIN_AXIS_MOTION_PARAMETERS.millimetersPerRotation
    );

    static_assert(
        MotionParameters.millimetersPerRotation <=
        MAX_AXIS_MOTION_PARAMETERS.millimetersPerRotation
    );

    static_assert(
        MotionParameters.motorStepsPerRotation >=
        MIN_AXIS_MOTION_PARAMETERS.motorStepsPerRotation
    );

    static_assert(
        MotionParameters.motorStepsPerRotation <=
        MAX_AXIS_MOTION_PARAMETERS.motorStepsPerRotation
    );

    static_assert(
        MotionParameters.driverStepDivider >=
        MIN_AXIS_MOTION_PARAMETERS.driverStepDivider
    );

    static_assert(
        MotionParameters.driverStepDivider <=
        MAX_AXIS_MOTION_PARAMETERS.driverStepDivider
    );

    static_assert(
        MotionParameters.stepErrorMargin >=
        MIN_AXIS_MOTION_PARAMETERS.stepErrorMargin
    );

    static_assert(
        MotionParameters.stepErrorMargin <=
        MAX_AXIS_MOTION_PARAMETERS.stepErrorMargin
    );
};

inline constexpr AxisMotionConfigValidator<X_AXIS_MOTION_PARAMETERS>
    X_AXIS_MOTION_VALIDATOR {};
inline constexpr AxisMotionConfigValidator<Y_AXIS_MOTION_PARAMETERS>
    Y_AXIS_MOTION_VALIDATOR {};
inline constexpr AxisMotionConfigValidator<Z_AXIS_MOTION_PARAMETERS>
    Z_AXIS_MOTION_VALIDATOR {};
}