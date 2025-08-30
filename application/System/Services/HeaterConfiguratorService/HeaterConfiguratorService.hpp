#pragma once

#include "IHeaterConfiguratorService.hpp"
#include "application/System/Drivers/Logger/ILogger.hpp"
#include "application/System/Controllers/HeaterController/IHeaterController.hpp"

namespace ATC {
class HeaterConfiguratorService : public IHeaterConfiguratorService {
private:
    ILogger& logger_;
    IHeaterController& heaterController_;

    const uint8_t temperatureInCelsiusStep_;

public:
    HeaterConfiguratorService(
        ILogger& logger,
        IHeaterController& heaterController,
        uint8_t temperatureCelsiusStep
    );

    virtual void increaseTemperatureInCelsius() override;
    virtual void decreaseTemperatureInCelsius() override;
    virtual uint32_t getTemperatureInCelsius() const override;
    virtual void saveTemperatureInCelsius() override;

    virtual void turnOn() override;
    virtual void turnOff() override;
    virtual bool isOn() const override;
};
}
