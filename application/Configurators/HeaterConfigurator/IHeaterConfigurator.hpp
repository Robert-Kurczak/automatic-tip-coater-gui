#pragma once

#include <stdint.h>

namespace ATC {
class IHeaterConfigurator {
public:
    virtual void increaseTemperatureCelsius() = 0;
    virtual void decreaseTemperatureCelsius() = 0;
    virtual uint32_t getTemperatureInCelsius() const = 0;

    virtual void turnOn() = 0;
    virtual void turnOff() = 0;
};
}