#pragma once

#include "../IPersistentStorage.hpp"
#include "application/System/Drivers/Logger/ILogger.hpp"

namespace ATC {
class Eeprom : public IPersistentStorage {
private:
    ILogger& logger_;

public:
    Eeprom(ILogger& logger);

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