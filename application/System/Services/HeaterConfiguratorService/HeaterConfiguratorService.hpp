#pragma once

#include "IHeaterConfiguratorService.hpp"
#include "application/System/Controllers/HeaterController/IHeaterController.hpp"
#include "application/System/Controllers/PersistentStorageController/IPersistentStorageController.hpp"
#include "application/System/Controllers/PersistentStorageController/PersistentData/HeaterPersistentConfig.hpp"

namespace ATC {
class HeaterConfiguratorService : public IHeaterConfiguratorService {
private:
    IPersistentStorageController& persistentStorageController_;
    IHeaterController& heaterController_;

    const uint8_t temperatureInCelsiusStep_;

    bool bufferedHeaterOn_ = false;
    HeaterPersistentConfig bufferedPersistentConfig_ {
        .targetTemperatureInCelsius = 0
    };

public:
    HeaterConfiguratorService(
        IPersistentStorageController& persistentStorageController,
        IHeaterController& heaterController,
        uint8_t temperatureInCelsiusStep
    );

    virtual void resetBufferedConfig() override;

    virtual void increaseTemperatureInCelsius() override;
    virtual void decreaseTemperatureInCelsius() override;
    virtual uint32_t getTemperatureInCelsius() const override;
    virtual void saveTemperatureInCelsius() override;

    virtual void turnOn() override;
    virtual void turnOff() override;
    virtual bool isOn() const override;
    virtual void saveHeaterState() override;
};
}
