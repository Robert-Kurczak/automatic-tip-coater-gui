#pragma once

#include "application/System/Ports/ISpi.hpp"
#include "main.h"

namespace ATC {
class Spi : public ISpi {
private:
    SPI_HandleTypeDef& spiHandle_;
    const uint32_t speedInKilohertz_;

public:
    Spi(SPI_HandleTypeDef& spiHandle, uint32_t speedInKilohertz_);

    virtual void sendData(const std::span<const uint8_t>& data) override;
    virtual void receiveData(
        const std::span<uint8_t>& outputBuffer
    ) override;
    virtual void sendAndReceiveData(
        const std::span<const uint8_t>& data,
        const std::span<uint8_t>& outputBuffer
    ) override;

    [[nodiscard]] uint32_t getSpeedInKilohertz() const override;
};
}
