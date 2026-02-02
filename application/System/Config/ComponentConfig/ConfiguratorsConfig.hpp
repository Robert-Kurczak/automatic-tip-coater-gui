#pragma once
#include "application/System/Services/AxisConfiguratorService/AxisConfiguratorParameters.hpp"
#include "application/System/Services/HeaterConfiguratorService/HeaterConfiguratorParameters.hpp"
#include "application/System/Services/SpindleConfiguratorService/SpindleConfiguratorParameters.hpp"

namespace ATC {
inline constexpr AxisConfiguratorParameters
    X_AXIS_CONFIGURATOR_PARAMETERS {
        .positionStepInMicrometers = 1'000,
        .speedStepInMillimetersPerSecond = 1,
        .speedShowcasePositionInMicrometers = 5'000,
        .minPositionInMicrometers = 1'000,
        .maxPositionInMicrometers = 100'000,
        .minSpeedInMillimetersPerSecond = 1,
        .maxSpeedInMillimetersPerSecond = 200,
    };

inline constexpr AxisConfiguratorParameters
    Y_AXIS_CONFIGURATOR_PARAMETERS {
        .positionStepInMicrometers = 1'000,
        .speedStepInMillimetersPerSecond = 1,
        .speedShowcasePositionInMicrometers = 5'000,
        .minPositionInMicrometers = 1'000,
        .maxPositionInMicrometers = 100'000,
        .minSpeedInMillimetersPerSecond = 1,
        .maxSpeedInMillimetersPerSecond = 200,
    };

inline constexpr AxisConfiguratorParameters
    Z_AXIS_CONFIGURATOR_PARAMETERS {
        .positionStepInMicrometers = 1'000,
        .speedStepInMillimetersPerSecond = 1,
        .speedShowcasePositionInMicrometers = 5'000,
        .minPositionInMicrometers = 1'000,
        .maxPositionInMicrometers = 100'000,
        .minSpeedInMillimetersPerSecond = 1,
        .maxSpeedInMillimetersPerSecond = 200,
    };

inline constexpr SpindleConfiguratorParameters
    SPINDLE_CONFIGURATOR_PARAMETERS {
        .showcaseRotationTimeInMillis = 300,
        .speedPercentStep = 1,
        .rotationTimeStepInMillis = 5
    };

inline constexpr HeaterConfiguratorParameters
    HEATER_CONFIGURATOR_PARAMETERS {
        .temperatureStepInCelsius = 1.0F,
        .minTemperatureInCelsius = 0.0F,
        .maxTemperatureInCelsius = 300.0F
    };
}