#include "Eeprom.hpp"

namespace ATC {
Eeprom::Eeprom(ILogger& logger) : logger_(logger) {}

void Eeprom::read(
    uint32_t address,
    const std::span<uint8_t>& outputBuffer
) {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
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
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
}
}