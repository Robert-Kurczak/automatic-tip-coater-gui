#include "Thermistor.hpp"

namespace ATC {
Thermistor::Thermistor(ILogger& logger) : logger_(logger) {}

void Thermistor::init() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
}

uint32_t Thermistor::getCelsius() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement

    return 100;
}
}