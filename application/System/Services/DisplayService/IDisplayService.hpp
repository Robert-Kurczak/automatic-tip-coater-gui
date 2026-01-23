#pragma once

#include "application/Utils/Math.hpp"

#include <span>
#include <cstdint>

namespace ATC {
class IDisplayService {
public:
    IDisplayService() = default;
    IDisplayService(const IDisplayService&) = delete;
    IDisplayService& operator=(const IDisplayService&) = delete;
    IDisplayService(IDisplayService&&) = delete;
    IDisplayService& operator=(IDisplayService&&) = delete;
    virtual ~IDisplayService() = default;

    virtual void draw(
        const std::span<const uint16_t>& framebuffer,
        const Rectangle& window
    ) = 0;

    virtual void draw(const std::span<const uint16_t>& framebuffer) = 0;
};
}