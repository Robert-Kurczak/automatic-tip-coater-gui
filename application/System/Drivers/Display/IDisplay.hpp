#pragma once

#include "application/Utils/Math.hpp"

#include <cstdint>
#include <span>

namespace ATC {
class IDisplay {
public:
    IDisplay(const IDisplay&) = delete;
    IDisplay& operator=(const IDisplay&) = delete;
    IDisplay(IDisplay&& other) = delete;
    IDisplay& operator=(IDisplay&& other) = delete;

    IDisplay() = default;
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