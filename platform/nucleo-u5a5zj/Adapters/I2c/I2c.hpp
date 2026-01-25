#pragma once

#include "application/System/Ports/II2c.hpp"
#include "main.h"

namespace ATC {
class I2c : public II2c {
private:
    I2C_HandleTypeDef& i2cHandle_;

public:
    I2c(I2C_HandleTypeDef& i2cHandle);

    virtual void sendData(
        DeviceAddress deviceAddress,
        std::span<uint8_t> data
    ) override;

    virtual void sendDataToExternalMemory(
        DeviceAddress deviceAddress,
        MemoryAddress memoryAddress,
        MemoryAddressSize memoryAddressSize,
        std::span<uint8_t> data
    ) override;

    virtual void receiveData(
        DeviceAddress deviceAddress,
        std::span<uint8_t> outputBuffer
    ) override;

    virtual void receiveDataFromExternalMemory(
        DeviceAddress deviceAddress,
        MemoryAddress memoryAddress,
        MemoryAddressSize memoryAddressSize,
        std::span<uint8_t> outputBuffer
    ) override;
};
}