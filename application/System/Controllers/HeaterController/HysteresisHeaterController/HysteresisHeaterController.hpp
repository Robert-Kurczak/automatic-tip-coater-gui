#pragma once

#include "../IHeaterController.hpp"
#include "application/System/Drivers/Logger/ILogger.hpp"
#include "application/System/Drivers/Switch/ISwitch.hpp"
#include "application/System/Drivers/TemperatureSensor/ITemperatureSensor.hpp"

namespace ATC {
class HysteresisHeaterController : public IHeaterController {
private:
    ILogger& logger_;
    ISwitch& heaterSwitch_;
    ITemperatureSensor& temperatureSensor_;

    uint32_t targetTemperatureInCelsius_ = 0;

public:
    HysteresisHeaterController(
        ILogger& logger,
        ISwitch& heaterSwitch,
        ITemperatureSensor& temperatureSensor
    );

    virtual void init(const HeaterPersistentConfig& config) override;
    virtual void tick() override;

    virtual void turnOn() override;
    virtual void turnOff() override;
    virtual bool isOn() const override;

    virtual void setTargetTemperatureInCelsius(uint32_t value) override;
    virtual uint32_t getTargetTemperatureInCelsius() const override;

    virtual bool isAtTargetTemperature() const override;
};
}