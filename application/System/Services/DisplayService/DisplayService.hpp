#pragma once

#include "IDisplayService.hpp"
#include "application/system/Drivers/Display/IDisplay.hpp"

namespace ATC {
class DisplayService : public IDisplayService {
private:
    IDisplay& display_;

public:
    DisplayService(IDisplay& display);

    virtual void draw(
        const std::span<const uint16_t>& framebuffer,
        const Rectangle& window
    ) override;

    virtual void draw(
        const std::span<const uint16_t>& framebuffer
    ) override;
};
}
