#include "HysteresisHeaterController.hpp"

#include "application/Utils/Logger.hpp"

namespace ATC {

void HysteresisHeaterController::controlTemperature() {
    const float currentTemperatureInCelsius =
        temperatureSensor_.getCelsius();

    const bool isBelowMinimum =
        currentTemperatureInCelsius <
        targetTemperatureInCelsius_ - hysteresisMarginInCelsius_;

    const bool isAboveMaximum =
        currentTemperatureInCelsius >
        targetTemperatureInCelsius_ + hysteresisMarginInCelsius_;

    if (isBelowMinimum) {
        heaterSwitch_.turnOn();
    } else if (isAboveMaximum) {
        heaterSwitch_.turnOff();
    }
}

HysteresisHeaterController::HysteresisHeaterController(
    ILoggerSink& loggerSink,
    IOutputSwitch& heaterSwitch,
    ITemperatureSensor& temperatureSensor,
    float hysteresisMarginInCelsius
) :
    loggerSink_(loggerSink),
    heaterSwitch_(heaterSwitch),
    temperatureSensor_(temperatureSensor),
    hysteresisMarginInCelsius_(hysteresisMarginInCelsius) {}

void HysteresisHeaterController::init(
    const HeaterPersistentConfig& config
) {
    targetTemperatureInCelsius_ = config.targetTemperatureInCelsius;

    heaterSwitch_.init();
    heaterSwitch_.turnOff();

    temperatureSensor_.init();
}

void HysteresisHeaterController::tick() {
    if (isOn_) {
        controlTemperature();
    }
}

void HysteresisHeaterController::turnOn() {
    isOn_ = true;
}

void HysteresisHeaterController::turnOff() {
    heaterSwitch_.turnOff();
    isOn_ = false;
}

bool HysteresisHeaterController::isOn() const {
    return isOn_;
};

void HysteresisHeaterController::setTargetTemperatureInCelsius(
    float value
) {
    if (value < hysteresisMarginInCelsius_) {
        log(loggerSink_,
            LogLevel::Error,
            "Target heater temperature {}*C "
            "cannot be lower that hysteresis margin: {}*C\n"
            "Using old target value: {}",
            value,
            hysteresisMarginInCelsius_,
            targetTemperatureInCelsius_);

        return;
    }

    targetTemperatureInCelsius_ = value;
}

float HysteresisHeaterController::
    getTargetTemperatureInCelsius() const {
    return targetTemperatureInCelsius_;
}

bool HysteresisHeaterController::isAtTargetTemperature() const {
    const uint32_t currentTemperatureInCelsius =
        temperatureSensor_.getCelsius();

    const bool isAboveMinimum =
        currentTemperatureInCelsius >=
        targetTemperatureInCelsius_ - hysteresisMarginInCelsius_;

    const bool isBelowMaximum =
        currentTemperatureInCelsius <=
        targetTemperatureInCelsius_ + hysteresisMarginInCelsius_;

    return isAboveMinimum and isBelowMaximum;
}
}