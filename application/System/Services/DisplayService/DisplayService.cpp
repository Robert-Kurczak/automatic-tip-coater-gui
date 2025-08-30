#include "DisplayService.hpp"

namespace ATC {
DisplayService::DisplayService(IDisplay& display) : display_(display) {}

void DisplayService::draw(
    const std::span<const uint16_t>& framebuffer,
    const Rectangle& window
) {
    display_.draw(framebuffer, window);
}

void DisplayService::draw(const std::span<const uint16_t>& framebuffer) {
    display_.draw(framebuffer);
}
}