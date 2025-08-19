#pragma once

#include "application/Math/Math.hpp"

#include <span>
#include <stdint.h>

namespace ATC {
class IFramebufferDisplay {
public:
    virtual void init() = 0;
    virtual void drawTestPattern(const uint8_t colorOffset = 0) = 0;
    virtual void draw(
        const std::span<const uint16_t>& framebuffer,
        const Rectangle& window
    ) = 0;
    virtual void draw(const std::span<const uint16_t>& framebuffer) = 0;
};
}