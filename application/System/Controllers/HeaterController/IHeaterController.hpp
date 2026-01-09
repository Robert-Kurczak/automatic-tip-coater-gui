#pragma once

#include "application/System/Controllers/PersistentStorageController/PersistentData/HeaterPersistentConfig.hpp"

#include <cstdint>

namespace ATC {
class IHeaterController {
public:
    IHeaterController() = default;
    IHeaterController(const IHeaterController&) = delete;
    IHeaterController& operator=(const IHeaterController&) = delete;
    IHeaterController(IHeaterController&&) = delete;
    IHeaterController& operator=(IHeaterController&&) = delete;
    virtual ~IHeaterController() = default;

    virtual void init(const HeaterPersistentConfig& config) = 0;
    virtual void tick() = 0;

    virtual void turnOn() = 0;
    virtual void turnOff() = 0;
    [[nodiscard]] virtual bool isOn() const = 0;

    virtual void setTargetTemperatureInCelsius(uint32_t value) = 0;
    [[nodiscard]] virtual uint32_t
    getTargetTemperatureInCelsius() const = 0;

    [[nodiscard]] virtual bool isAtTargetTemperature() const = 0;
};
}