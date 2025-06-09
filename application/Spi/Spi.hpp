#pragma once

#include "main.h"

#include <span>
#include <stdint.h>

// TODO add fullduplex transfer
// TODO add config methods, like setSpeed?

namespace ATC {
class Spi {
private:
    SPI_HandleTypeDef& spiHandle_;

public:
    Spi(SPI_HandleTypeDef& spiHandle);
    void sendData(const std::span<const uint8_t>& data);
    void receiveData(const std::span<uint8_t>& outputBuffer);
};
}