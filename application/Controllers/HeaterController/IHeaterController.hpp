#pragma once

#include <functional>
#include <stdint.h>

namespace ATC {
class IHeaterController {
public:
    virtual ~IHeaterController() = default;

    virtual void init() = 0;
    virtual void tick() = 0;

    virtual void turnOn() = 0;
    virtual void turnOff() = 0;

    virtual void setTargetTemperatureInCelsius(uint32_t value) = 0;
    virtual uint32_t getTargetTemperatureInCelsius() const = 0;

    virtual bool isAtTargetTemperature() const = 0;
};
}