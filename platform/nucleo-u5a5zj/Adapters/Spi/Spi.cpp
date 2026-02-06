#include "Spi.hpp"

#include "stm32u5xx_hal_def.h"
#include "stm32u5xx_hal_spi.h"

#include <cstdint>

namespace ATC {
Spi::Spi(SPI_HandleTypeDef& spiHandle, uint32_t speedInKilohertz) :
    spiHandle_(spiHandle),
    speedInKilohertz_(speedInKilohertz) {}

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

void Spi::sendAndReceiveData(
    const std::span<const uint8_t>& data,
    const std::span<uint8_t>& outputBuffer
) {
    HAL_SPI_TransmitReceive(
        &spiHandle_,
        data.data(),
        outputBuffer.data(),
        data.size(),
        HAL_MAX_DELAY
    );
}

uint32_t Spi::getSpeedInKilohertz() const {
    return speedInKilohertz_;
}
}
