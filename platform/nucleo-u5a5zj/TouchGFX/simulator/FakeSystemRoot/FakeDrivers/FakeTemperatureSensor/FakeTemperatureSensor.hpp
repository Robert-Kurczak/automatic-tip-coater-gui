#pragma once

#include "application/System/Drivers/LoggerSink/ILoggerSink.hpp"
#include "application/System/Drivers/TemperatureSensor/ITemperatureSensor.hpp"

#include <string>

namespace ATC {
class FakeTemperatureSensor : public ITemperatureSensor {
private:
    ILoggerSink& loggerSink_;
    std::string name_;

public:
    FakeTemperatureSensor(ILoggerSink& loggerSink, std::string&& name);

    virtual void init() override;

    virtual float getCelsius() override;
};
}