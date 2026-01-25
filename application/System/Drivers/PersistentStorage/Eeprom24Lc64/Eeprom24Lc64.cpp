#include "Eeprom24Lc64.hpp"

#include "application/System/Ports/II2c.hpp"

namespace ATC {
static constexpr uint8_t MEMORY_ADDRESS_SIZE = 2;

Eeprom24Lc64::Eeprom24Lc64(II2c& i2c, uint8_t deviceAddress) :
    i2c_(i2c),
    deviceAddress_(deviceAddress) {}

void Eeprom24Lc64::init() {}

void Eeprom24Lc64::read(
    uint16_t address,
    std::span<uint8_t> outputBuffer
) {
    i2c_.receiveDataFromExternalMemory(
        II2c::DeviceAddress {deviceAddress_},
        II2c::MemoryAddress {address},
        II2c::MemoryAddressSize {MEMORY_ADDRESS_SIZE},
        outputBuffer
    );
}

void Eeprom24Lc64::write(uint16_t address, std::span<uint8_t> data) {
    i2c_.sendDataToExternalMemory(
        II2c::DeviceAddress {deviceAddress_},
        II2c::MemoryAddress {address},
        II2c::MemoryAddressSize {MEMORY_ADDRESS_SIZE},
        data
    );
}
}