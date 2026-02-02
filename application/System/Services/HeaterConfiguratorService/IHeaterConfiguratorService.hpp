#pragma once

#include "application/System/Controllers/PersistentStorageController/PersistentData/HeaterPersistentConfig.hpp"

namespace ATC {
class IHeaterConfiguratorService {
public:
    IHeaterConfiguratorService(const IHeaterConfiguratorService&) =
        delete;

    IHeaterConfiguratorService& operator=(
        const IHeaterConfiguratorService&
    ) = delete;

    IHeaterConfiguratorService(IHeaterConfiguratorService&& other) =
        delete;

    IHeaterConfiguratorService& operator=(
        IHeaterConfiguratorService&& other
    ) = delete;

    IHeaterConfiguratorService() = default;
    virtual ~IHeaterConfiguratorService() = default;

    virtual void resetBufferedConfig() = 0;

    virtual void increaseTemperatureInCelsius() = 0;
    virtual void decreaseTemperatureInCelsius() = 0;
    [[nodiscard]] virtual float getTemperatureInCelsius() const = 0;
    virtual void saveTemperatureInCelsius() = 0;

    virtual void turnOn() = 0;
    virtual void turnOff() = 0;
    [[nodiscard]] virtual bool isOn() const = 0;
    virtual void saveHeaterState() = 0;

    [[nodiscard]] virtual HeaterPersistentConfig
    getStoredConfig() const = 0;
};
}