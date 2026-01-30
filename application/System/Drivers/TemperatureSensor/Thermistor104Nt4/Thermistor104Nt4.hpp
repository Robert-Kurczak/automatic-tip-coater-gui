#pragma once

#include "../ITemperatureSensor.hpp"
#include "application/System/Drivers/LoggerSink/ILoggerSink.hpp"
#include "application/System/Ports/IAdc.hpp"

namespace ATC {
class Thermistor104Nt4 : public ITemperatureSensor {
private:
    ILoggerSink& loggerSink_;
    IAdc& adc_;

    void checkAdcConfig() const;

public:
    Thermistor104Nt4(ILoggerSink& loggerSink, IAdc& adc);

    void init() override;

    [[nodiscard]] float getCelsius() override;
};
}