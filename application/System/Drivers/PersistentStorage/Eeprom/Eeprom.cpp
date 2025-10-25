#include "Eeprom.hpp"

namespace ATC {
Eeprom::Eeprom(ILoggerSink& loggerSink) : loggerSink_(loggerSink) {}

void Eeprom::read(
    uint32_t address,
    const std::span<uint8_t>& outputBuffer
) {
    logger_.log(
        LogLevel::Error,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
}

void Eeprom::write(
    uint32_t address,
    const std::span<const uint8_t>& data
) {
    logger_.log(
        LogLevel::Error,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
}
}