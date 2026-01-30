#include "Thermistor104Nt4.hpp"

#include "Thermistor104Nt4Table.hpp"
#include "application/Utils/Logger.hpp"
#include <source_location>

namespace ATC {
void Thermistor104Nt4::checkAdcConfig() const {
    constexpr uint8_t expectedResolutionBits = 10;

    if (adc_.getResolutionBits() != expectedResolutionBits) {
        log(
            loggerSink_,
            LogLevel::Error,
            "Expected 10 bit ADC in {}, instead got: {}",
            std::source_location::current().file_name(),
            adc_.getResolutionBits()
        );
    }
}

Thermistor104Nt4::Thermistor104Nt4(ILoggerSink& loggerSink, IAdc& adc) :
    loggerSink_(loggerSink),
    adc_(adc) {}

void Thermistor104Nt4::init() {
    adc_.init();
}

float Thermistor104Nt4::getCelsius() {
    const uint16_t rawValue = adc_.readRaw();
    return THERMISTOR_104NT4_TABLE.at(rawValue);
}
}
