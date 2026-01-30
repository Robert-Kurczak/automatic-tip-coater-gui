#pragma once

#include "../IHeaterController.hpp"
#include "application/System/Drivers/LoggerSink/ILoggerSink.hpp"
#include "application/System/Drivers/OutputSwitch/IOutputSwitch.hpp"
#include "application/System/Drivers/TemperatureSensor/ITemperatureSensor.hpp"

#include <cstdint>

namespace ATC {
class HysteresisHeaterController : public IHeaterController {
private:
    ILoggerSink& loggerSink_;
    IOutputSwitch& heaterSwitch_;
    ITemperatureSensor& temperatureSensor_;
    const float hysteresisMarginInCelsius_;

    float targetTemperatureInCelsius_ = 0;
    bool isOn_ = false;

    void controlTemperature();

public:
    HysteresisHeaterController(
        ILoggerSink& loggerSink,
        IOutputSwitch& heaterSwitch,
        ITemperatureSensor& temperatureSensor,
        float hysteresisMarginInCelsius
    );

    void init(const HeaterPersistentConfig& config) override;
    void tick() override;

    void turnOn() override;
    void turnOff() override;
    [[nodiscard]] bool isOn() const override;

    void setTargetTemperatureInCelsius(float value) override;
    [[nodiscard]] float getTargetTemperatureInCelsius() const override;

    [[nodiscard]] bool isAtTargetTemperature() const override;
};
}