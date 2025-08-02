#pragma once

#include "application/Math/Math.hpp"

#include <stdint.h>

namespace ATC {
class ITouchController {
public:
    virtual void init() = 0;

    virtual bool isPressed() = 0;
    virtual uint16_t readRawPressure() = 0;
    virtual Vector2 readPosition() = 0;
};
}