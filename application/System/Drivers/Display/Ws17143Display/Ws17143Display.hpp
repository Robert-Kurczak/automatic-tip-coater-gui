#pragma once

#include "../IDisplay.hpp"
#include "application/System/Ports/IFlexibleMemoryController.hpp"
#include "application/System/Ports/IGpioPin.hpp"
#include "application/System/Ports/ISystemClock.hpp"

#include <cstdint>
#include <span>

namespace ATC {
struct Ws17143DisplayPinout {
    // NOLINTBEGIN(cppcoreguidelines-avoid-const-or-ref-data-members)
    IGpioPin& lcdResetPin_;
    // NOLINTEND(cppcoreguidelines-avoid-const-or-ref-data-members)
};

class Ws17143Display : public IDisplay {
private:
    const Ws17143DisplayPinout& pinout_;
    IFlexibleMemoryController& flexibleMemoryController_;
    ISystemClock& systemClock_;

    void setWindow(const Rectangle& window);

    void initResetLcdPin();
    void resetLcd();
    void initSettings();
    void exitSleepState();
    void enableDisplay();
    void setAllPixelsOff();

public:
    static constexpr uint16_t WIDTH_ = 480;
    static constexpr uint16_t HEIGHT_ = 800;

    Ws17143Display(
        const Ws17143DisplayPinout& pinout,
        IFlexibleMemoryController& flexibleMemoryController,
        ISystemClock& systemClock
    );

    void init() override;
    void drawTestPattern(uint8_t seed) override;
    void draw(
        const std::span<const uint16_t>& framebuffer,
        const Rectangle& window
    ) override;
    void draw(const std::span<const uint16_t>& framebuffer) override;
};
}