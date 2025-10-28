#include "Eeprom.hpp"

#include "application/Utils/Logger.hpp"

namespace ATC {
Eeprom::Eeprom(ILoggerSink& loggerSink) : loggerSink_(loggerSink) {}

void Eeprom::read(
    uint32_t address,
    const std::span<uint8_t>& outputBuffer
) {
    log(loggerSink_,
        LogLevel::Error,
        std::source_location::current(),
        "Not implemented");
    // TODO implement
}

void Eeprom::write(
    uint32_t address,
    const std::span<const uint8_t>& data
) {
    log(loggerSink_,
        LogLevel::Error,
        std::source_location::current(),
        "Not implemented");
    // TODO implement
}
}