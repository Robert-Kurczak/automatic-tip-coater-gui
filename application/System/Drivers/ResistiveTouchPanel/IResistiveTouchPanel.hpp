#pragma once

#include <stdint.h>

namespace ATC {
class IResistiveTouchPanel {
public:
    virtual ~IResistiveTouchPanel() = default;

    virtual void init() = 0;

    virtual bool isTouchDetected() = 0;

    virtual uint16_t readRawX() = 0;
    virtual uint16_t readRawY() = 0;
    virtual uint16_t readRawZ() = 0;
};
}