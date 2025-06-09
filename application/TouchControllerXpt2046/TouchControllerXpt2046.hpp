#pragma once

#include "application/GpioPin/GpioPin.hpp"
#include "application/Math/Math.hpp"
#include "application/Spi/Spi.hpp"

#include <stdint.h>

namespace ATC {
class TouchControllerXpt2046 {
private:
    static const uint8_t readXCommand_ = 0xD0;
    static const uint8_t readYCommand_ = 0x90;

    Spi& spi_;
    GpioPin& chipSelectPin_;
    GpioPin& touchInterruptPin_;
    Rectangle rawWorkingArea_;
    const Vector2 pixelResolution_;

    uint16_t sendReadCommand(uint8_t command);

public:
    TouchControllerXpt2046(
        Spi& spi,
        GpioPin& chipSelectPin,
        GpioPin& touchInterruptPin,
        Rectangle rawWorkingArea,
        Vector2 pixelResolution
    );

    void init();

    bool isTouched();

    uint16_t readRawX();
    uint16_t readRawY();

    uint16_t readX();
    uint16_t readY();
};
}