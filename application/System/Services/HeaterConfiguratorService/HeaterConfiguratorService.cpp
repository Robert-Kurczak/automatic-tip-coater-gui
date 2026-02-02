#include "HeaterConfiguratorService.hpp"

namespace ATC {
HeaterConfiguratorService::HeaterConfiguratorService(
    IPersistentStorageController& persistentStorageController,
    IHeaterController& heaterController,
    float temperatureInCelsiusStep
) :
    persistentStorageController_(persistentStorageController),
    heaterController_(heaterController),
    temperatureInCelsiusStep_(temperatureInCelsiusStep) {}

void HeaterConfiguratorService::resetBufferedConfig() {
    bufferedHeaterOn_ = heaterController_.isOn();
    bufferedPersistentConfig_.targetTemperatureInCelsius =
        heaterController_.getTargetTemperatureInCelsius();
}

void HeaterConfiguratorService::increaseTemperatureInCelsius() {
    bufferedPersistentConfig_.targetTemperatureInCelsius +=
        temperatureInCelsiusStep_;
}

void HeaterConfiguratorService::decreaseTemperatureInCelsius() {
    bufferedPersistentConfig_.targetTemperatureInCelsius -=
        temperatureInCelsiusStep_;
}

float HeaterConfiguratorService::getTemperatureInCelsius() const {
    return bufferedPersistentConfig_.targetTemperatureInCelsius;
}

void HeaterConfiguratorService::saveTemperatureInCelsius() {
    heaterController_.setTargetTemperatureInCelsius(
        bufferedPersistentConfig_.targetTemperatureInCelsius
    );

    persistentStorageController_.saveHeaterConfig(
        bufferedPersistentConfig_
    );
}

void HeaterConfiguratorService::turnOn() {
    bufferedHeaterOn_ = true;
}

void HeaterConfiguratorService::turnOff() {
    bufferedHeaterOn_ = false;
}

bool HeaterConfiguratorService::isOn() const {
    return bufferedHeaterOn_;
}

void HeaterConfiguratorService::saveHeaterState() {
    if (bufferedHeaterOn_) {
        heaterController_.turnOn();
    } else {
        heaterController_.turnOff();
    }
}

HeaterPersistentConfig HeaterConfiguratorService::
    getStoredConfig() const {
    return HeaterPersistentConfig {
        .targetTemperatureInCelsius =
            heaterController_.getTargetTemperatureInCelsius()
    };
}
}