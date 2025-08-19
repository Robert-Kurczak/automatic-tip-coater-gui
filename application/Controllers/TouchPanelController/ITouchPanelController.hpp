#pragma once

#include "application/Math/Math.hpp"

#include <stdint.h>

namespace ATC {
class ITouchPanelController {
public:
    virtual void init() = 0;

    virtual Vector2 readPosition() = 0;
};
}