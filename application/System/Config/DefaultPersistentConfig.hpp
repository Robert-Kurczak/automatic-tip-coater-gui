#pragma once

#include "application/System/Controllers/PersistentStorageController/PersistentData/AxisPersistentConfig.hpp"
#include "application/System/Controllers/PersistentStorageController/PersistentData/HeaterPersistentConfig.hpp"
#include "application/System/Controllers/PersistentStorageController/PersistentData/SpindlePersistentConfig.hpp"

namespace ATC {
inline constexpr AxisPersistentConfig DEFAULT_X_AXIS_CONFIG {
    .startPosition = 0,
    .endPosition = 100,
    .speedInMillimetersPerSecond = 10
};

inline constexpr AxisPersistentConfig DEFAULT_Y_AXIS_CONFIG {
    .startPosition = 0,
    .endPosition = 100,
    .speedInMillimetersPerSecond = 10
};

inline constexpr AxisPersistentConfig DEFAULT_Z_AXIS_CONFIG {
    .startPosition = 0,
    .endPosition = 100,
    .speedInMillimetersPerSecond = 10
};

inline constexpr SpindlePersistentConfig DEFAULT_SPINDLE_CONFIG {
    .speedPercent = 50,
    .isDirectionClockwise = true,
    .timedRotationInMillis = 3000
};

inline constexpr HeaterPersistentConfig DEFAULT_HEATER_CONFIG {
    .targetTemperatureInCelsius = 200
};
}