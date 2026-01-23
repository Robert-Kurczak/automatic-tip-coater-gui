#include "Xpt2046TouchPanel.hpp"

#include "application/System/Ports/IGpioPin.hpp"

#include <array>

namespace ATC {
static constexpr uint8_t READ_X_COMMAND_ = 0xD0;
static constexpr uint8_t READ_Y_COMMAND_ = 0x90;
static constexpr uint8_t READ_Z1_COMMAND_ = 0xB0;
static constexpr uint8_t READ_Z2_COMMAND_ = 0xC0;

uint16_t Xpt2046TouchPanel::transferReadCommand(uint8_t command) {
    pinout_.chipSelectPin.setLow();

    std::array<uint8_t, 2> outputBuffer {};

    spi_.sendData(std::span {&command, sizeof(command)});
    spi_.receiveData(outputBuffer);

    pinout_.chipSelectPin.setHigh();

    constexpr uint8_t bitsToShift = 8;
    return ((outputBuffer[0] << bitsToShift) | outputBuffer[1]) >> 4;
}

Xpt2046TouchPanel::Xpt2046TouchPanel(
    Xpt2046TouchPanelPinout& pinout,
    ISpi& spi
) :
    pinout_(pinout),
    spi_(spi) {}

void Xpt2046TouchPanel::init() {
    pinout_.touchInterruptPin.init(GpioMode::Input, GpioPull::NoPull);

    pinout_.chipSelectPin.init(GpioMode::Output, GpioPull::NoPull);
    pinout_.chipSelectPin.setHigh();
}

bool Xpt2046TouchPanel::isTouchDetected() {
    return pinout_.touchInterruptPin.isLow();
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