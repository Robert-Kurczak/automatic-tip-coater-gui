#include "Thermistor.hpp"

namespace ATC {
Thermistor::Thermistor(ILoggerSink& loggerSink) : loggerSink_(loggerSink) {}

void Thermistor::init() {
    logger_.log(
        LogLevel::Error,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
}

uint32_t Thermistor::getCelsius() {
    logger_.log(
        LogLevel::Error,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement

    return 100;
}
}