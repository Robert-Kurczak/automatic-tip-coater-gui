#include "ThermistorHeater.hpp"

#include <source_location>

namespace ATC {
ThermistorHeater::ThermistorHeater(ILogger& logger) : logger_(logger) {}

void ThermistorHeater::init() {}

void ThermistorHeater::tick() {}

void ThermistorHeater::startTestTask(HeaterTestTaskCallback callback) {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement

    HeaterTestResults results {.temperatureSuccess = true};

    callback(results);
}

void ThermistorHeater::setOn() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
}

void ThermistorHeater::setOff() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
}

void ThermistorHeater::saveState() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
}

bool ThermistorHeater::isOn() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
    return false;
}

void ThermistorHeater::increaseTemperature() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
}

void ThermistorHeater::decreaseTemperature() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
}

void ThermistorHeater::saveTemperature() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
}

uint32_t ThermistorHeater::getTemperature() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
    return 200;
}
}