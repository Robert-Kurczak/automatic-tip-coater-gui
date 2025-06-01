#pragma once

#include <span>
#include <stdint.h>

#include "main.h"

// TODO add fullduplex transfer
// TODO add config methods, like setSpeed?
class Spi {
private:
    SPI_HandleTypeDef& spiHandle;

public:
    Spi(SPI_HandleTypeDef& spiHandle_);
    void sendData(const std::span<const uint8_t>& data);
    void receiveData(const std::span<uint8_t>& outputBuffer);
};