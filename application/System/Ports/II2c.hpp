#pragma once

#include <span>
#include <cstdint>

namespace ATC {
class II2c {
public:
    struct DeviceAddress {
        uint8_t value;
        constexpr bool operator==(const DeviceAddress&) const = default;
    };

    struct MemoryAddress {
        uint16_t value;
        constexpr bool operator==(const MemoryAddress&) const = default;
    };

    struct MemoryAddressSize {
        uint8_t value;
        constexpr bool operator==(const MemoryAddressSize&) const = default;
    };

    II2c() = default;
    II2c(const II2c&) = delete;
    II2c& operator=(const II2c&) = delete;
    II2c(II2c&&) = delete;
    II2c& operator=(II2c&&) = delete;
    virtual ~II2c() = default;

    virtual void sendData(
        DeviceAddress deviceAddress,
        std::span<uint8_t> data
    ) = 0;

    virtual void sendDataToExternalMemory(
        DeviceAddress deviceAddress,
        MemoryAddress memoryAddress,
        MemoryAddressSize memoryAddressSize,
        std::span<uint8_t> data
    ) = 0;

    virtual void receiveData(
        DeviceAddress deviceAddress,
        std::span<uint8_t> outputBuffer
    ) = 0;

    virtual void receiveDataFromExternalMemory(
        DeviceAddress deviceAddress,
        MemoryAddress memoryAddress,
        MemoryAddressSize memoryAddressSize,
        std::span<uint8_t> outputBuffer
    ) = 0;
};
}
