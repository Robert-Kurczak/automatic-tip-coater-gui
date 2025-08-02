#include "Spi.hpp"

namespace ATC {
Spi::Spi(SPI_HandleTypeDef& spiHandle) : spiHandle_(spiHandle) {}

void Spi::sendData(const std::span<const uint8_t>& data) {
    HAL_SPI_Transmit(
        &spiHandle_, data.data(), data.size(), HAL_MAX_DELAY
    );
}

void Spi::receiveData(const std::span<uint8_t>& outputBuffer) {
    HAL_SPI_Receive(
        &spiHandle_,
        outputBuffer.data(),
        outputBuffer.size(),
        HAL_MAX_DELAY
    );
}
}