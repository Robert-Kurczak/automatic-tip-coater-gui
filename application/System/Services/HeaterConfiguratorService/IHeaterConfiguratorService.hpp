#pragma once

#include <stdint.h>

namespace ATC {
class IHeaterConfiguratorService {
public:
    virtual ~IHeaterConfiguratorService() = default;

    virtual void resetBufferedConfig() = 0;

    virtual void increaseTemperatureInCelsius() = 0;
    virtual void decreaseTemperatureInCelsius() = 0;
    virtual uint32_t getTemperatureInCelsius() const = 0;
    virtual void saveTemperatureInCelsius() = 0;

    virtual void turnOn() = 0;
    virtual void turnOff() = 0;
    virtual bool isOn() const = 0;
    virtual void saveHeaterState() = 0;
};
}