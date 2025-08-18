#include "HeaterConfigurator.hpp"

namespace ATC {
HeaterConfigurator::HeaterConfigurator(
    IHeaterController& heaterController,
    uint8_t temperatureCelsiusStep
) :
    heaterController_(heaterController),
    temperatureCelsiusStep_(temperatureCelsiusStep) {}

void HeaterConfigurator::increaseTemperatureCelsius() {
    heaterController_.setTargetTemperatureInCelsius(
        heaterController_.getTargetTemperatureInCelsius() +
        temperatureCelsiusStep_
    );
}

void HeaterConfigurator::decreaseTemperatureCelsius() {
    heaterController_.setTargetTemperatureInCelsius(
        heaterController_.getTargetTemperatureInCelsius() -
        temperatureCelsiusStep_
    );
}

uint32_t HeaterConfigurator::getTemperatureInCelsius() const {
    return heaterController_.getTargetTemperatureInCelsius();
}

void HeaterConfigurator::turnOn() {
    heaterController_.turnOn();
}

void HeaterConfigurator::turnOff() {
    heaterController_.turnOff();
}
}