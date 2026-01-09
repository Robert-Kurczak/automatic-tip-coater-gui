#pragma once

#include "application/Utils/Math.hpp"

#include <cstdint>
#include <span>

namespace ATC {
class IDisplay {
public:
    IDisplay() = default;
    IDisplay(const IDisplay&) = delete;
    IDisplay& operator=(const IDisplay&) = delete;
    IDisplay(IDisplay&&) = delete;
    IDisplay& operator=(IDisplay&&) = delete;
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