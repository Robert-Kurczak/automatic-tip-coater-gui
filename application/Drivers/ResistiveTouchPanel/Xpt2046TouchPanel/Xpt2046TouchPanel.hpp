#pragma once

#include "../IResistiveTouchPanel.hpp"
#include "application/Ports/IGpioPin.hpp"
#include "application/Ports/ISpi.hpp"

namespace ATC {
struct Xpt2046TouchPanelPinout {
    IGpioPin& chipSelectPin;
    IGpioPin& touchInterruptPin;
};

class Xpt2046TouchPanel : public IResistiveTouchPanel {
private:
    Xpt2046TouchPanelPinout& pinout_;
    ISpi& spi_;

    static constexpr uint8_t READ_X_COMMAND_ = 0xD0;
    static constexpr uint8_t READ_Y_COMMAND_ = 0x90;
    static constexpr uint8_t READ_Z1_COMMAND_ = 0xB0;
    static constexpr uint8_t READ_Z2_COMMAND_ = 0xC0;

    uint16_t transferReadCommand(uint8_t command);

public:
    Xpt2046TouchPanel(Xpt2046TouchPanelPinout& pinout, ISpi& spi);

    virtual void init() override;

    virtual bool isTouchDetected() override;

    virtual uint16_t readRawX() override;
    virtual uint16_t readRawY() override;
    virtual uint16_t readRawZ() override;
};
}
