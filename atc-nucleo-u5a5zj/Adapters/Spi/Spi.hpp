#pragma once

#include "application/Ports/ISpi.hpp"
#include "main.h"

namespace ATC {
class Spi : public ISpi {
private:
    SPI_HandleTypeDef& spiHandle_;

public:
    Spi(SPI_HandleTypeDef& spiHandle);

    virtual void sendData(const std::span<const uint8_t>& data) override;
    virtual void receiveData(
        const std::span<uint8_t>& outputBuffer
    ) override;
};
}