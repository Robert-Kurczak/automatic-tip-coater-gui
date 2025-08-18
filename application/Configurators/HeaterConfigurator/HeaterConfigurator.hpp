#pragma once

#include "IHeaterConfigurator.hpp"
#include "application/Controllers/HeaterController/IHeaterController.hpp"

namespace ATC {
class HeaterConfigurator : public IHeaterConfigurator {
private:
    IHeaterController& heaterController_;

    const uint8_t temperatureCelsiusStep_;

public:
    HeaterConfigurator(
        IHeaterController& heaterController,
        uint8_t temperatureCelsiusStep
    );

    virtual void increaseTemperatureCelsius() override;
    virtual void decreaseTemperatureCelsius() override;
    virtual uint32_t getTemperatureInCelsius() const override;

    virtual void turnOn() override;
    virtual void turnOff() override;
};
}