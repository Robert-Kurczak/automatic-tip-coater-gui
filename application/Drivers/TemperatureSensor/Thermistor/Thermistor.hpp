#pragma once

#include "../ITemperatureSensor.hpp"
#include "application/System/Logger/ILogger.hpp"

namespace ATC {
class Thermistor : public ITemperatureSensor {
private:
    ILogger& logger_;

public:
    Thermistor(ILogger& logger);

    virtual void init() override;

    virtual uint32_t getCelsius() override;
};
}