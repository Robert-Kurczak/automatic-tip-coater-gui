#pragma once

#include "../ITemperatureSensor.hpp"
#include "application/System/Drivers/LoggerSink/ILoggerSink.hpp"

namespace ATC {
class Thermistor : public ITemperatureSensor {
private:
    ILoggerSink& loggerSink_;

public:
    Thermistor(ILoggerSink& loggerSink);

    void init() override;

    uint32_t getCelsius() override;
};
}