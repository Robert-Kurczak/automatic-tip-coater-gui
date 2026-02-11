#pragma once

#include "../IResistiveTouchPanel.hpp"
#include "application/System/Drivers/LoggerSink/ILoggerSink.hpp"
#include "application/System/Ports/IGpioPin.hpp"
#include "application/System/Ports/ISpi.hpp"

namespace ATC {

struct Xpt2046TouchPanelPinout {
    // NOLINTBEGIN(cppcoreguidelines-avoid-const-or-ref-data-members)
    IGpioPin& chipSelectPin;
    IGpioPin& touchInterruptPin;
    // NOLINTEND(cppcoreguidelines-avoid-const-or-ref-data-members)
};

class Xpt2046TouchPanel : public IResistiveTouchPanel {
private:
    ILoggerSink& loggerSink_;
    Xpt2046TouchPanelPinout& pinout_;
    ISpi& spi_;

    uint16_t transferReadCommand(uint8_t command);

    void verifySpiSpeed();

public:
    static constexpr uint8_t READ_X_COMMAND = 0xD0;
    static constexpr uint8_t READ_Y_COMMAND = 0x90;
    static constexpr uint8_t READ_Z1_COMMAND = 0xB0;
    static constexpr uint8_t READ_Z2_COMMAND = 0xC0;

    Xpt2046TouchPanel(
        ILoggerSink& loggerSink,
        Xpt2046TouchPanelPinout& pinout,
        ISpi& spi
    );

    void init() override;

    bool isTouchDetected() override;

    uint16_t readRawX() override;
    uint16_t readRawY() override;
    uint16_t readRawZ() override;
};
}
