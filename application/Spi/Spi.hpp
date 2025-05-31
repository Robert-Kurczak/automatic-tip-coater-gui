#pragma once

#include <span>
#include <stdint.h>

#include "main.h"

class Spi {
private:
    SPI_HandleTypeDef& spiHandle;

public:
    Spi(SPI_HandleTypeDef& spiHandle_);
    void sendData(const std::span<uint8_t>& data);
    void receiveData(const std::span<uint8_t>& outputBuffer);
};