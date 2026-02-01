#pragma once

#include "application/System/Controllers/PersistentStorageController/PersistentData/AxisPersistentConfig.hpp"

#include <cstdint>

namespace ATC {
class IAxisConfiguratorService {
public:
    IAxisConfiguratorService() = default;
    IAxisConfiguratorService(const IAxisConfiguratorService&) = delete;
    IAxisConfiguratorService& operator=(const IAxisConfiguratorService&) =
        delete;
    IAxisConfiguratorService(IAxisConfiguratorService&&) = delete;
    IAxisConfiguratorService& operator=(IAxisConfiguratorService&&) =
        delete;
    virtual ~IAxisConfiguratorService() = default;

    virtual void resetBufferedConfig() = 0;

    virtual void showcaseStartPosition() = 0;
    virtual void increaseStartPosition() = 0;
    virtual void decreaseStartPosition() = 0;
    virtual void saveStartPosition() = 0;
    [[nodiscard]] virtual uint32_t
    getStartPositionInMicrometers() const = 0;

    virtual void showcaseEndPosition() = 0;
    virtual void increaseEndPosition() = 0;
    virtual void decreaseEndPosition() = 0;
    virtual void saveEndPosition() = 0;
    [[nodiscard]] virtual uint32_t getEndPositionInMicrometers() const = 0;

    virtual void showcaseSpeed() = 0;
    virtual void increaseSpeed() = 0;
    virtual void decreaseSpeed() = 0;
    virtual void saveSpeed() = 0;
    [[nodiscard]] virtual uint32_t
    getSpeedInMillimetersPerSecond() const = 0;

    [[nodiscard]] virtual AxisPersistentConfig getStoredConfig() const = 0;
};
}