#include "Xpt2046TouchPanel.hpp"

namespace ATC {
uint16_t Xpt2046TouchPanel::transferReadCommand(uint8_t command) {
    pinout_.chipSelectPin.setLow();

    uint8_t outputBuffer[2];

    spi_.sendData({&command, 1});
    spi_.receiveData(outputBuffer);

    pinout_.chipSelectPin.setHigh();

    return ((outputBuffer[0] << 8) | outputBuffer[1]) >> 4;
}

Xpt2046TouchPanel::Xpt2046TouchPanel(
    Xpt2046TouchPanelPinout& pinout,
    ISpi& spi
) :
    pinout_(pinout),
    spi_(spi) {}

void Xpt2046TouchPanel::init() {
    pinout_.touchInterruptPin.setInputMode();

    pinout_.chipSelectPin.setOutputMode();
    pinout_.chipSelectPin.setHigh();
}

bool Xpt2046TouchPanel::isTouchDetected() {
    return !pinout_.touchInterruptPin.isHigh();
}

uint16_t Xpt2046TouchPanel::readRawX() {
    return transferReadCommand(READ_X_COMMAND_);
}

uint16_t Xpt2046TouchPanel::readRawY() {
    return transferReadCommand(READ_Y_COMMAND_);
}

uint16_t Xpt2046TouchPanel::readRawZ() {
    const uint16_t rawZ1Value = transferReadCommand(READ_Z1_COMMAND_);
    const uint16_t rawZ2Value = transferReadCommand(READ_Z2_COMMAND_);

    const uint16_t rawPressure = (rawZ2Value > rawZ1Value)
                                     ? (rawZ2Value - rawZ1Value)
                                     : (rawZ1Value - rawZ2Value);

    return rawPressure;
}
}