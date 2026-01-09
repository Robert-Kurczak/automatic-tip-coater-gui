#pragma once

#include <cstdint>

namespace ATC {
class IResistiveTouchPanel {
public:
    IResistiveTouchPanel() = default;
    IResistiveTouchPanel(const IResistiveTouchPanel&) = delete;
    IResistiveTouchPanel& operator=(const IResistiveTouchPanel&) = delete;
    IResistiveTouchPanel(IResistiveTouchPanel&&) = delete;
    IResistiveTouchPanel& operator=(IResistiveTouchPanel&&) = delete;

    virtual ~IResistiveTouchPanel() = default;

    virtual void init() = 0;

    virtual bool isTouchDetected() = 0;

    virtual uint16_t readRawX() = 0;
    virtual uint16_t readRawY() = 0;
    virtual uint16_t readRawZ() = 0;
};
}