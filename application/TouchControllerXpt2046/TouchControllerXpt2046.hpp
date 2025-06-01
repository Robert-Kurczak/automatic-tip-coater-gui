#pragma once

#include "application/GpioPin/GpioPin.hpp"
#include "application/Spi/Spi.hpp"

#include <stdint.h>

class TouchControllerXpt2046 {
private:
    static const uint8_t readXCommand = 0xD0;
    static const uint8_t readYCommand = 0x90;

    Spi& spi;
    GpioPin& chipSelectPin;
    GpioPin& touchInterruptPin;

    const uint16_t xPixels;
    const uint16_t yPixels;

    const uint16_t maxRawValueX;
    const uint16_t maxRawValueY;

    uint16_t sendReadCommand(uint8_t command);

public:
    TouchControllerXpt2046(
        Spi& spi_,
        GpioPin& chipSelectPin_,
        GpioPin& touchInterruptPin_,
        uint16_t xPixels_,
        uint16_t yPixels_,
        uint16_t maxRawValueX_,
        uint16_t maxRawValueY_
    );

    void init();

    bool isTouched();

    uint16_t readRawX();
    uint16_t readRawY();

    uint16_t readX();
    uint16_t readY();
};