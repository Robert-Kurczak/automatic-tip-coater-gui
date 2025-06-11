#include "TouchControllerXpt2046.hpp"

namespace ATC {
uint16_t TouchControllerXpt2046::transferReadCommand(uint8_t command) {
    pinout_.chipSelectPin_.setLow();

    uint8_t outputBuffer[2];

    spi_.sendData({&command, 1});
    spi_.receiveData(outputBuffer);

    pinout_.chipSelectPin_.setHigh();

    return ((outputBuffer[0] << 8) | outputBuffer[1]) >> 4;
}

TouchControllerXpt2046::TouchControllerXpt2046(
    Xpt2046Pinout& pinout,
    Spi& spi,
    Rectangle rawWorkingArea,
    Vector2 pixelResolution
) :
    pinout_(pinout),
    spi_(spi),
    rawWorkingArea_(rawWorkingArea),
    pixelResolution_(pixelResolution) {}

void TouchControllerXpt2046::init() {
    pinout_.touchInterruptPin_.setInputMode();

    pinout_.chipSelectPin_.setOutputMode();
    pinout_.chipSelectPin_.setHigh();
}

bool TouchControllerXpt2046::isTouched() {
    static const uint16_t pressureTreshold = 1500;

    const bool isTouchDetected = !pinout_.touchInterruptPin_.isHigh();
    const bool isPressedEnough = readRawPressure() <= pressureTreshold;

    return isTouchDetected && isPressedEnough;
}

uint16_t TouchControllerXpt2046::readRawX() {
    if (!isTouched()) {
        return UINT16_MAX;
    }

    return transferReadCommand(readXCommand_);
}

uint16_t TouchControllerXpt2046::readRawY() {
    if (!isTouched()) {
        return UINT16_MAX;
    }

    return transferReadCommand(readYCommand_);
}

uint16_t TouchControllerXpt2046::readRawPressure() {
    const uint16_t rawZ1Value = transferReadCommand(readZ1Command_);
    const uint16_t rawZ2Value = transferReadCommand(readZ2Command_);

    const uint16_t rawPressure = (rawZ2Value > rawZ1Value)
                                     ? (rawZ2Value - rawZ1Value)
                                     : (rawZ1Value - rawZ2Value);

    return rawPressure;
}

uint16_t TouchControllerXpt2046::readX() {
    const uint16_t rawXValue = readRawX();

    return (rawXValue - rawWorkingArea_.xStart_) * pixelResolution_.x_ /
           (rawWorkingArea_.xEnd_ - rawWorkingArea_.xStart_);
}

// TODO handle underflows when rawValue comes up smaller that minRawValue
uint16_t TouchControllerXpt2046::readY() {
    const uint16_t rawYValue = readRawY();

    return (rawYValue - rawWorkingArea_.yStart_) * pixelResolution_.y_ /
           (rawWorkingArea_.yEnd_ - rawWorkingArea_.yStart_);
}
}