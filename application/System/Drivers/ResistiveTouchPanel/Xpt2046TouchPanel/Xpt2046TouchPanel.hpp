#pragma once

#include "../IResistiveTouchPanel.hpp"
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
    Xpt2046TouchPanelPinout& pinout_;
    ISpi& spi_;

    uint16_t transferReadCommand(uint8_t command);

public:
    Xpt2046TouchPanel(Xpt2046TouchPanelPinout& pinout, ISpi& spi);

    void init() override;

    bool isTouchDetected() override;

    uint16_t readRawX() override;
    uint16_t readRawY() override;
    uint16_t readRawZ() override;
};
}
