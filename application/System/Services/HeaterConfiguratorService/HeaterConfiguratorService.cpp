#include "HeaterConfiguratorService.hpp"

#include "application/System/Services/HeaterConfiguratorService/HeaterConfiguratorParameters.hpp"

namespace ATC {
HeaterConfiguratorService::HeaterConfiguratorService(
    IPersistentStorageController& persistentStorageController,
    IHeaterController& heaterController,
    HeaterConfiguratorParameters parameters
) :
    persistentStorageController_(persistentStorageController),
    heaterController_(heaterController),
    parameters_(parameters) {}

void HeaterConfiguratorService::resetBufferedConfig() {
    bufferedHeaterOn_ = heaterController_.isOn();
    bufferedPersistentConfig_.targetTemperatureInCelsius =
        heaterController_.getTargetTemperatureInCelsius();
}

void HeaterConfiguratorService::increaseTemperatureInCelsius() {
    float& currentValue =
        bufferedPersistentConfig_.targetTemperatureInCelsius;

    const float step = parameters_.temperatureStepInCelsius;
    const float maxBound = parameters_.maxTemperatureInCelsius;

    if (currentValue > maxBound - step) {
        return;
    }

    currentValue += step;
}

void HeaterConfiguratorService::decreaseTemperatureInCelsius() {
    float& currentValue =
        bufferedPersistentConfig_.targetTemperatureInCelsius;

    const float step = parameters_.temperatureStepInCelsius;
    const float minBound = parameters_.minTemperatureInCelsius;

    if (currentValue < minBound + step) {
        return;
    }

    currentValue -= step;
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