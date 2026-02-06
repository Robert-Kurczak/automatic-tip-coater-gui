#include "../ComponentConfig/ConfiguratorsConfig.hpp"
#include "../ComponentConfig/DefaultPersistentConfig.hpp"
#include "application/System/Controllers/PersistentStorageController/PersistentData/AxisPersistentConfig.hpp"
#include "application/System/Services/AxisConfiguratorService/AxisConfiguratorParameters.hpp"

namespace ATC {

template<
    AxisPersistentConfig PersistentConfig,
    AxisConfiguratorParameters ConfiguratorParameters>
struct AxisConfigValidator {
    static_assert(
        PersistentConfig.startPositionInMicrometers >=
        ConfiguratorParameters.minPositionInMicrometers
    );

    static_assert(
        PersistentConfig.startPositionInMicrometers <
        PersistentConfig.endPositionInMicrometers
    );

    static_assert(
        PersistentConfig.endPositionInMicrometers <=
        ConfiguratorParameters.maxPositionInMicrometers
    );

    static_assert(
        PersistentConfig.endPositionInMicrometers >
        PersistentConfig.startPositionInMicrometers
    );

    static_assert(
        PersistentConfig.speedInMillimetersPerSecond >=
        ConfiguratorParameters.minSpeedInMillimetersPerSecond
    );

    static_assert(
        PersistentConfig.speedInMillimetersPerSecond <=
        ConfiguratorParameters.maxSpeedInMillimetersPerSecond
    );
};

inline constexpr AxisConfigValidator<
    DEFAULT_X_AXIS_CONFIG,
    X_AXIS_CONFIGURATOR_PARAMETERS>
    X_AXIS_VALIDATOR {};

inline constexpr AxisConfigValidator<
    DEFAULT_Y_AXIS_CONFIG,
    Y_AXIS_CONFIGURATOR_PARAMETERS>
    Y_AXIS_VALIDATOR {};

inline constexpr AxisConfigValidator<
    DEFAULT_Z_AXIS_CONFIG,
    Z_AXIS_CONFIGURATOR_PARAMETERS>
    Z_AXIS_VALIDATOR {};
}