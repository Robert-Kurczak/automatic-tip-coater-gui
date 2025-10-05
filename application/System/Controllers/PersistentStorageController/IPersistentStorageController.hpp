#pragma once

#include "application/System/PersistentConfig/AxisPersistentConfig.hpp"
#include "application/System/PersistentConfig/HeaterPersistentConfig.hpp"
#include "application/System/PersistentConfig/SpindlePersistentConfig.hpp"

namespace ATC {
class IPersistentStorageController {
public:
    virtual void init() = 0;

    virtual void saveXAxisConfig(const AxisPersistentConfig& config) = 0;
    virtual void saveYAxisConfig(const AxisPersistentConfig& config) = 0;
    virtual void saveZAxisConfig(const AxisPersistentConfig& config) = 0;
    virtual void saveSpindleConfig(
        const SpindlePersistentConfig& config
    ) = 0;
    virtual void saveHeaterConfig(
        const HeaterPersistentConfig& config
    ) = 0;
};
}