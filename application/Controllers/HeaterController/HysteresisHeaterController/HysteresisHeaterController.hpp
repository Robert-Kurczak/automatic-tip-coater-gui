#pragma once

#include "../IHeaterController.hpp"
#include "application/Drivers/Switch/ISwitch.hpp"
#include "application/Drivers/TemperatureSensor/ITemperatureSensor.hpp"
#include "application/System/Logger/ILogger.hpp"

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

    virtual void init() override;
    virtual void tick() override;

    virtual void turnOn() override;
    virtual void turnOff() override;

    virtual void setTargetTemperatureInCelsius(uint32_t value) override;
    virtual uint32_t getTargetTemperatureInCelsius() const override;

    virtual bool isAtTargetTemperature() const override;
};
}