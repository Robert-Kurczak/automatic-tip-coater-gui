#include "FakeTemperatureSensor.hpp"

#include "application/Utils/Logger.hpp"

namespace ATC {
FakeTemperatureSensor::FakeTemperatureSensor(
    ILoggerSink& loggerSink,
    std::string&& name
) :
    loggerSink_(loggerSink),
    name_(name) {}

void FakeTemperatureSensor::init() {
    log(loggerSink_, LogLevel::Debug, "{} initialized", name_);
};

uint32_t FakeTemperatureSensor::getCelsius() {
    static uint8_t calls = 0;

    if (calls < UINT8_MAX) {
        calls++;
    }

    return 20 + (10 * calls);
};
}