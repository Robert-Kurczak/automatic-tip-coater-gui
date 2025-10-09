#pragma once

#include "PersistentData/AxisPersistentConfig.hpp"
#include "PersistentData/HeaterPersistentConfig.hpp"
#include "PersistentData/SpindlePersistentConfig.hpp"

namespace ATC {
class IPersistentStorageController {
public:
    virtual ~IPersistentStorageController() = default;

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