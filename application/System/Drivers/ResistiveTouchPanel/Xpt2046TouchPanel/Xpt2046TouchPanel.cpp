#include "Xpt2046TouchPanel.hpp"

#include "application/System/Ports/IGpioPin.hpp"
#include "application/Utils/Logger.hpp"

#include <array>

namespace ATC {

uint16_t Xpt2046TouchPanel::transferReadCommand(uint8_t command) {
    pinout_.chipSelectPin.setLow();

    std::array<uint8_t, 2> outputBuffer {};

    spi_.sendData(std::span {&command, sizeof(command)});
    spi_.receiveData(outputBuffer);

    pinout_.chipSelectPin.setHigh();

    constexpr uint8_t bitsToShift = 8;
    return ((outputBuffer[0] << bitsToShift) | outputBuffer[1]) >> 4;
}

void Xpt2046TouchPanel::verifySpiSpeed() {
    constexpr uint32_t nanosecondsInSecond = 1'000'000'000;
    constexpr uint32_t hertzInKilohertz = 1'000;

    constexpr uint32_t minimumClockPulseInNanoseconds = 500;
    constexpr uint32_t maxClockInKilohertz =
        nanosecondsInSecond /
        (minimumClockPulseInNanoseconds * hertzInKilohertz);

    const uint32_t spiClockInKilohertz = spi_.getSpeedInKilohertz();

    if (spiClockInKilohertz > maxClockInKilohertz) {
        log(loggerSink_,
            LogLevel::Error,
            "SPI Clock: {}khz is too big for XPT2046 Touch Panel: {}khz",
            spiClockInKilohertz,
            maxClockInKilohertz);
    }
}

Xpt2046TouchPanel::Xpt2046TouchPanel(
    ILoggerSink& loggerSink,
    Xpt2046TouchPanelPinout& pinout,
    ISpi& spi
) :
    loggerSink_(loggerSink),
    pinout_(pinout),
    spi_(spi) {}

void Xpt2046TouchPanel::init() {
    pinout_.touchInterruptPin.init(GpioMode::Input, GpioPull::NoPull);

    pinout_.chipSelectPin.init(GpioMode::Output, GpioPull::NoPull);
    pinout_.chipSelectPin.setHigh();

    verifySpiSpeed();
}

bool Xpt2046TouchPanel::isTouchDetected() {
    return pinout_.touchInterruptPin.isLow();
}

uint16_t Xpt2046TouchPanel::readRawX() {
    return transferReadCommand(READ_X_COMMAND);
}

uint16_t Xpt2046TouchPanel::readRawY() {
    return transferReadCommand(READ_Y_COMMAND);
}

uint16_t Xpt2046TouchPanel::readRawZ() {
    const uint16_t rawZ1Value = transferReadCommand(READ_Z1_COMMAND);
    const uint16_t rawZ2Value = transferReadCommand(READ_Z2_COMMAND);

    const uint16_t rawPressure = (rawZ2Value > rawZ1Value)
                                     ? (rawZ2Value - rawZ1Value)
                                     : (rawZ1Value - rawZ2Value);

    return rawPressure;
}
}