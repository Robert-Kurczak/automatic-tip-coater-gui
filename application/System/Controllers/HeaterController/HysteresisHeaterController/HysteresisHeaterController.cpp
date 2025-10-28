#include "HysteresisHeaterController.hpp"

#include "application/Utils/Logger.hpp"

namespace ATC {
HysteresisHeaterController::HysteresisHeaterController(
    ILoggerSink& loggerSink,
    ISwitch& heaterSwitch,
    ITemperatureSensor& temperatureSensor
) :
    loggerSink_(loggerSink),
    heaterSwitch_(heaterSwitch),
    temperatureSensor_(temperatureSensor) {}

void HysteresisHeaterController::init(
    const HeaterPersistentConfig& config
) {
    targetTemperatureInCelsius_ = config.targetTemperatureInCelsius;

    heaterSwitch_.init();
    temperatureSensor_.init();
}

void HysteresisHeaterController::tick() {}

void HysteresisHeaterController::turnOn() {
    log(loggerSink_,
        LogLevel::Error,
        std::source_location::current(),
        "Not implemented");
    // TODO implement
}

void HysteresisHeaterController::turnOff() {
    log(loggerSink_,
        LogLevel::Error,
        std::source_location::current(),
        "Not implemented");
    // TODO implement
}

bool HysteresisHeaterController::isOn() const {
    log(loggerSink_,
        LogLevel::Error,
        std::source_location::current(),
        "Not implemented");
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