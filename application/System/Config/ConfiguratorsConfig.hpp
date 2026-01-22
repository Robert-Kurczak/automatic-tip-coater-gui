#pragma once
#include "application/System/Services/AxisConfiguratorService/AxisConfiguratorParameters.hpp"
#include "application/System/Services/SpindleConfiguratorService/SpindleConfiguratorParameters.hpp"

namespace ATC {
inline constexpr AxisConfiguratorParameters
    X_AXIS_CONFIGURATOR_PARAMETERS {
        .positionStep = 5,
        .speedStep = 1,
        .speedShowcasePosition = 20
    };

inline constexpr AxisConfiguratorParameters
    Y_AXIS_CONFIGURATOR_PARAMETERS {
        .positionStep = 5,
        .speedStep = 1,
        .speedShowcasePosition = 20
    };

inline constexpr AxisConfiguratorParameters
    Z_AXIS_CONFIGURATOR_PARAMETERS {
        .positionStep = 5,
        .speedStep = 1,
        .speedShowcasePosition = 20
    };

inline constexpr SpindleConfiguratorParameters
    SPINDLE_CONFIGURATOR_PARAMETERS {
        .showcaseRotationTimeMillis = 300,
        .speedPercentStep = 1,
        .rotationTimeStepMillis = 5
    };
}
