#pragma once

#include "../ITemperatureSensor.hpp"
#include "application/System/Drivers/LoggerSink/ILoggerSink.hpp"

namespace ATC {
class Thermistor : public ITemperatureSensor {
private:
    ILoggerSink& loggerSink_;

public:
    Thermistor(ILoggerSink& loggerSink);

    virtual void init() override;

    virtual uint32_t getCelsius() override;
};
}