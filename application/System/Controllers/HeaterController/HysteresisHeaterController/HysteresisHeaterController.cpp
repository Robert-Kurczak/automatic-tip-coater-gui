#include "HysteresisHeaterController.hpp"

namespace ATC {
HysteresisHeaterController::HysteresisHeaterController(
    ILogger& logger,
    ISwitch& heaterSwitch,
    ITemperatureSensor& temperatureSensor
) :
    logger_(logger),
    heaterSwitch_(heaterSwitch),
    temperatureSensor_(temperatureSensor) {}

void HysteresisHeaterController::init() {
    heaterSwitch_.init();
    temperatureSensor_.init();
}

void HysteresisHeaterController::tick() {}

void HysteresisHeaterController::turnOn() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
}

void HysteresisHeaterController::turnOff() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
}

bool HysteresisHeaterController::isOn() const {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
    return false;
};

void HysteresisHeaterController::setTargetTemperatureInCelsius(
    uint32_t value
) {
    targetTemperatureInCelsius_ = value;
}

uint32_t HysteresisHeaterController::
    getTargetTemperatureInCelsius() const {
    return targetTemperatureInCelsius_;
}

bool HysteresisHeaterController::isAtTargetTemperature() const {
    // TODO add error margin
    return temperatureSensor_.getCelsius() == targetTemperatureInCelsius_;
}
}