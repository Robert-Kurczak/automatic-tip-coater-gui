#pragma once

#include "application/Utils/Math.hpp"

#include <span>
#include <stdint.h>

namespace ATC {
class IDisplay {
public:
    virtual ~IDisplay() = default;

    virtual void init() = 0;
    virtual void drawTestPattern(uint8_t seed) = 0;
    virtual void draw(
        const std::span<const uint16_t>& framebuffer,
        const Rectangle& window
    ) = 0;
    virtual void draw(const std::span<const uint16_t>& framebuffer) = 0;
};
}