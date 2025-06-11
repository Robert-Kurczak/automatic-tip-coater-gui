#pragma once

#include "application/GpioPin/GpioPin.hpp"
#include "application/Math/Math.hpp"
#include "application/Spi/Spi.hpp"

#include <stdint.h>

namespace ATC {
struct Xpt2046Pinout {
    GpioPin& chipSelectPin_;
    GpioPin& touchInterruptPin_;
};

class TouchControllerXpt2046 {
private:
    static const uint8_t readXCommand_ = 0xD0;
    static const uint8_t readYCommand_ = 0x90;
    static const uint8_t readZ1Command_ = 0xB0;
    static const uint8_t readZ2Command_ = 0xC0;

    Xpt2046Pinout& pinout_;
    Spi& spi_;
    Rectangle rawWorkingArea_;
    const Vector2 pixelResolution_;

    uint16_t transferReadCommand(uint8_t command);

public:
    TouchControllerXpt2046(
        Xpt2046Pinout& pinout,
        Spi& spi,
        Rectangle rawWorkingArea,
        Vector2 pixelResolution
    );

    void init();

    bool isTouched();

    uint16_t readRawX();
    uint16_t readRawY();
    uint16_t readRawPressure();

    uint16_t readX();
    uint16_t readY();
};
}