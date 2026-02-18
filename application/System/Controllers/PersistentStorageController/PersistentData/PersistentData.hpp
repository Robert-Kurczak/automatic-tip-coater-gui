#include "AxisPersistentConfig.hpp"
#include "HeaterPersistentConfig.hpp"
#include "SpindlePersistentConfig.hpp"

#include <cstdint>

namespace ATC {
struct PersistentData {
    static constexpr uint32_t EXPECTED_SIGNATURE = 0xDEADBEEF;

    AxisPersistentConfig xAxisConfig;
    AxisPersistentConfig yAxisConfig;
    AxisPersistentConfig zAxisConfig;
    SpindlePersistentConfig spindleConfig;
    HeaterPersistentConfig heaterConfig;
    uint32_t signature;
    uint32_t checksum;

    constexpr bool operator==(const PersistentData&) const = default;
};
}