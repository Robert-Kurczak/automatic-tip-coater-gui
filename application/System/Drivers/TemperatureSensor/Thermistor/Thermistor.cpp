#include "Thermistor.hpp"

#include "application/Utils/Logger.hpp"

namespace ATC {
Thermistor::Thermistor(ILoggerSink& loggerSink) :
    loggerSink_(loggerSink) {}

void Thermistor::init() {
    log(loggerSink_,
        LogLevel::Error,
        std::source_location::current(),
        "Not implemented");
    // TODO implement
}

uint32_t Thermistor::getCelsius() {
    log(loggerSink_,
        LogLevel::Error,
        std::source_location::current(),
        "Not implemented");
    // TODO implement

    return 0;
}
}