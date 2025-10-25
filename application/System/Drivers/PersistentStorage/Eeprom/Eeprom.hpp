#pragma once

#include "../IPersistentStorage.hpp"
#include "application/System/Drivers/LoggerSink/ILoggerSink.hpp"

namespace ATC {
class Eeprom : public IPersistentStorage {
private:
    ILoggerSink& loggerSink_;

public:
    Eeprom(ILoggerSink& loggerSink);

    virtual void read(
        uint32_t address,
        const std::span<uint8_t>& outputBuffer
    ) override;

    virtual void write(
        uint32_t address,
        const std::span<const uint8_t>& data
    ) override;
};
}