#pragma once

#include "../IFramebufferDisplay.hpp"
#include "application/Hardware/FlexibleMemoryController/IFlexibleMemoryController.hpp"
#include "application/Ports/IDelayProvider.hpp"
#include "application/Ports/IGpioPin.hpp"

#include <span>
#include <stdint.h>

namespace ATC {
struct Ws17143DisplayPinout {
    IGpioPin& lcdResetPin_;
};

class Ws17143Display : public IFramebufferDisplay {
private:
    static const uint16_t WIDTH_ = 480;
    static const uint16_t HEIGHT_ = 800;

    const Ws17143DisplayPinout& pinout_;
    IFlexibleMemoryController& flexibleMemoryController_;
    IDelayProvider& delayProvider_;

    void setWindow(const Rectangle& window);

    void initResetLcdPin();
    void resetLcd();
    void initProprietaryHardwareSettings();
    void initProprietaryGammaSettings();
    void initRGB565Format();
    void exitSleepState();
    void enableDisplay();
    void setAllPixelsOff();
    void displayFramebuffer();

public:
    Ws17143Display(
        const Ws17143DisplayPinout& pinout,
        IFlexibleMemoryController& flexibleMemoryController,
        IDelayProvider& delayProvider
    );

    virtual void init() override;
    virtual void drawTestPattern(const uint8_t colorOffset) override;
    virtual void draw(
        const std::span<const uint16_t>& framebuffer,
        const Rectangle& window
    ) override;
    virtual void draw(
        const std::span<const uint16_t>& framebuffer
    ) override;
};
}