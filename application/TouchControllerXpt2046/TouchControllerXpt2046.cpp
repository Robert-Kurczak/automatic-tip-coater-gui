#include "TouchControllerXpt2046.hpp"

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
    uint16_t xPixels_,
    uint16_t yPixels_,
    uint16_t maxRawValueX_,
    uint16_t maxRawValueY_
) :
    spi(spi_),
    chipSelectPin(chipSelectPin_),
    xPixels(xPixels_),
    yPixels(yPixels_),
    maxRawValueX(maxRawValueX_),
    maxRawValueY(maxRawValueY_) {}

void TouchControllerXpt2046::init() {
    chipSelectPin.setOutputMode();
    chipSelectPin.setHigh();
}

uint16_t TouchControllerXpt2046::readRawX() {
    return sendReadCommand(readXCommand);
}

uint16_t TouchControllerXpt2046::readRawY() {
    return sendReadCommand(readYCommand);
}

uint16_t TouchControllerXpt2046::readX() {
    const uint16_t rawXValue = readRawX();

    return rawXValue * xPixels / maxRawValueX;
}

uint16_t TouchControllerXpt2046::readY() {
    const uint16_t rawYValue = readRawY();

    return rawYValue * yPixels / maxRawValueY;
}