#pragma once

namespace ATC {
struct HeaterPersistentConfig {
    float targetTemperatureInCelsius;

    constexpr bool operator==(const HeaterPersistentConfig&) const =
        default;
};
}