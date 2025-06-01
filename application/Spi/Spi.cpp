#include "Spi.hpp"
#include "main.h"

Spi::Spi(SPI_HandleTypeDef& spiHandle_) : spiHandle(spiHandle_) {}

void Spi::sendData(const std::span<const uint8_t>& data) {
    HAL_SPI_Transmit(&spiHandle, data.data(), data.size(), HAL_MAX_DELAY);
}

void Spi::receiveData(const std::span<uint8_t>& outputBuffer) {
    HAL_SPI_Receive(&spiHandle, outputBuffer.data(), outputBuffer.size(), HAL_MAX_DELAY);
}