#pragma once

#include "application/System/Controllers/AxisController/AxisConfig.hpp"
#include "application/System/Controllers/HeaterController/HeaterConfig.hpp"
#include "application/System/Controllers/SpindleController/SpindleConfig.hpp"

namespace ATC {
struct DefaultPersistentConfigProvider {
    static constexpr AxisConfig getXAxisConfig() {
        return AxisConfig {
            .startPosition = 100, .endPosition = 1000, .speed = 200
        };
    }

    static constexpr AxisConfig getYAxisConfig() {
        return AxisConfig {
            .startPosition = 100, .endPosition = 1000, .speed = 200
        };
    }

    static constexpr AxisConfig getZAxisConfig() {
        return AxisConfig {
            .startPosition = 100, .endPosition = 1000, .speed = 200
        };
    }

    static constexpr SpindleConfig getSpindleConfig() {
        return SpindleConfig {
            .spindleSpeedPercentage = 80,
            .isSpindleDirectionClockwise = true,
            .timedRotationInMillis = 3000,
        };
    }

    static constexpr HeaterConfig getHeaterConfig() {
        return HeaterConfig {.targetTemperatureInCelsius = 200};
    }
};
}