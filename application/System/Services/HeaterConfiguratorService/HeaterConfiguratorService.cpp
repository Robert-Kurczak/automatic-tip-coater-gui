#include "HeaterConfiguratorService.hpp"

namespace ATC {
HeaterConfiguratorService::HeaterConfiguratorService(
    ILogger& logger,
    IHeaterController& heaterController,
    uint8_t temperatureCelsiusStep
) :
    logger_(logger),
    heaterController_(heaterController),
    temperatureInCelsiusStep_(temperatureCelsiusStep) {}

void HeaterConfiguratorService::increaseTemperatureInCelsius() {
    heaterController_.setTargetTemperatureInCelsius(
        heaterController_.getTargetTemperatureInCelsius() +
        temperatureInCelsiusStep_
    );
}

void HeaterConfiguratorService::decreaseTemperatureInCelsius() {
    heaterController_.setTargetTemperatureInCelsius(
        heaterController_.getTargetTemperatureInCelsius() -
        temperatureInCelsiusStep_
    );
}

uint32_t HeaterConfiguratorService::getTemperatureInCelsius() const {
    return heaterController_.getTargetTemperatureInCelsius();
}

void HeaterConfiguratorService::saveTemperatureInCelsius() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
}

void HeaterConfiguratorService::turnOn() {
    heaterController_.turnOn();
}

void HeaterConfiguratorService::turnOff() {
    heaterController_.turnOff();
}

bool HeaterConfiguratorService::isOn() const {
    return heaterController_.isOn();
}
}