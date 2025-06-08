#include "TouchControllerXpt2046.hpp"

namespace ATC {
uint16_t TouchControllerXpt2046::sendReadCommand(uint8_t command) {
    chipSelectPin.setLow();

    uint8_t outputBuffer[2];

    spi.sendData({&command, 1});
    spi.receiveData(outputBuffer);

    chipSelectPin.setHigh();

    return ((outputBuffer[0] << 8) | outputBuffer[1]) >> 4;
}

TouchControllerXpt2046::TouchControllerXpt2046(
    Spi& spi_,
    GpioPin& chipSelectPin_,
    GpioPin& touchInterruptPin_,
    Rectangle rawWorkingArea_,
    Vector2 pixelResolution_
) :
    spi(spi_),
    chipSelectPin(chipSelectPin_),
    touchInterruptPin(touchInterruptPin_),
    rawWorkingArea(rawWorkingArea_),
    pixelResolution(pixelResolution_) {}

void TouchControllerXpt2046::init() {
    touchInterruptPin.setInputMode();

    chipSelectPin.setOutputMode();
    chipSelectPin.setHigh();
}

bool TouchControllerXpt2046::isTouched() {
    return !touchInterruptPin.isHigh();
}

uint16_t TouchControllerXpt2046::readRawX() {
    if (!isTouched()) {
        return UINT16_MAX;
    }

    return sendReadCommand(readXCommand);
}

uint16_t TouchControllerXpt2046::readRawY() {
    if (!isTouched()) {
        return UINT16_MAX;
    }

    return sendReadCommand(readYCommand);
}

uint16_t TouchControllerXpt2046::readX() {
    const uint16_t rawXValue = readRawX();

    return (rawXValue - rawWorkingArea.xStart) * pixelResolution.x /
           (rawWorkingArea.xEnd - rawWorkingArea.xStart);
}

// TODO handle underflows when rawValue comes up smaller that minRawValue
uint16_t TouchControllerXpt2046::readY() {
    const uint16_t rawYValue = readRawY();

    return (rawYValue - rawWorkingArea.yStart) * pixelResolution.y /
           (rawWorkingArea.yEnd - rawWorkingArea.yStart);
}
}