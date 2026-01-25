#include "I2c.hpp"

#include "stm32u5xx_hal_def.h"
#include "stm32u5xx_hal_i2c.h"

namespace ATC {
I2c::I2c(I2C_HandleTypeDef& i2cHandle) : i2cHandle_(i2cHandle) {}

void I2c::sendData(DeviceAddress deviceAddress, std::span<uint8_t> data) {
    HAL_I2C_Master_Transmit(
        &i2cHandle_,
        uint16_t(deviceAddress.value << 1),
        data.data(),
        data.size(),
        HAL_MAX_DELAY
    );
}

void I2c::sendDataToExternalMemory(
    DeviceAddress deviceAddress,
    MemoryAddress memoryAddress,
    MemoryAddressSize memoryAddressSize,
    std::span<uint8_t> data
) {
    HAL_I2C_Mem_Write(
        &i2cHandle_,
        uint16_t(deviceAddress.value << 1),
        memoryAddress.value,
        memoryAddressSize.value,
        data.data(),
        data.size(),
        HAL_MAX_DELAY
    );
}

void I2c::receiveData(
    DeviceAddress deviceAddress,
    std::span<uint8_t> outputBuffer
) {
    HAL_I2C_Master_Receive(
        &i2cHandle_,
        uint16_t(deviceAddress.value << 1),
        outputBuffer.data(),
        outputBuffer.size(),
        HAL_MAX_DELAY
    );
}

void I2c::receiveDataFromExternalMemory(
    DeviceAddress deviceAddress,
    MemoryAddress memoryAddress,
    MemoryAddressSize memoryAddressSize,
    std::span<uint8_t> outputBuffer
) {
    HAL_I2C_Mem_Read(
        &i2cHandle_,
        uint16_t(deviceAddress.value << 1),
        memoryAddress.value,
        memoryAddressSize.value,
        outputBuffer.data(),
        outputBuffer.size(),
        HAL_MAX_DELAY
    );
}
}
