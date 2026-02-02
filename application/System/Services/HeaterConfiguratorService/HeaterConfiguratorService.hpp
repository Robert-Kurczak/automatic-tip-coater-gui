#pragma once

#include "IHeaterConfiguratorService.hpp"
#include "application/System/Controllers/HeaterController/IHeaterController.hpp"
#include "application/System/Controllers/PersistentStorageController/IPersistentStorageController.hpp"
#include "application/System/Controllers/PersistentStorageController/PersistentData/HeaterPersistentConfig.hpp"
#include "application/System/Services/HeaterConfiguratorService/HeaterConfiguratorParameters.hpp"

namespace ATC {
class HeaterConfiguratorService : public IHeaterConfiguratorService {
private:
    IPersistentStorageController& persistentStorageController_;
    IHeaterController& heaterController_;
    const HeaterConfiguratorParameters parameters_;

    bool bufferedHeaterOn_ = false;
    HeaterPersistentConfig bufferedPersistentConfig_ {
        .targetTemperatureInCelsius = 0
    };

public:
    HeaterConfiguratorService(
        IPersistentStorageController& persistentStorageController,
        IHeaterController& heaterController,
        HeaterConfiguratorParameters parameters
    );

    void resetBufferedConfig() override;

    void increaseTemperatureInCelsius() override;
    void decreaseTemperatureInCelsius() override;
    [[nodiscard]] float getTemperatureInCelsius() const override;
    void saveTemperatureInCelsius() override;

    void turnOn() override;
    void turnOff() override;
    [[nodiscard]] bool isOn() const override;
    void saveHeaterState() override;

    [[nodiscard]] HeaterPersistentConfig getStoredConfig() const override;
};
}
