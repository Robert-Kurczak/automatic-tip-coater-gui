#pragma once

#include "../IPersistentStorage.hpp"
#include "application/System/Ports/II2c.hpp"

namespace ATC {
class Eeprom24Lc64 : public IPersistentStorage {
private:
    II2c& i2c_;
    const uint8_t deviceAddress_;

public:
    Eeprom24Lc64(II2c& i2c, uint8_t deviceAddress);

    void init() override;

    void read(uint16_t address, std::span<uint8_t> outputBuffer) override;

    void write(uint16_t address, std::span<uint8_t> data) override;
};
}