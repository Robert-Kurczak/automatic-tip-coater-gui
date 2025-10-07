#pragma once

#include "application/System/Controllers/AxisController/AxisConfig.hpp"
#include "application/System/Controllers/HeaterController/HeaterConfig.hpp"
#include "application/System/Controllers/SpindleController/SpindleConfig.hpp"

namespace ATC {
class IPersistentStorageController {
public:
    virtual ~IPersistentStorageController() = default;

    virtual void init() = 0;

    virtual void saveXAxisConfig(const AxisConfig& config) = 0;
    virtual void saveYAxisConfig(const AxisConfig& config) = 0;
    virtual void saveZAxisConfig(const AxisConfig& config) = 0;
    virtual void saveSpindleConfig(const SpindleConfig& config) = 0;
    virtual void saveHeaterConfig(const HeaterConfig& config) = 0;
};
}