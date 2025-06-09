#pragma once

#include "application/DelayProvider/DelayProvider.hpp"
#include "application/FlexibleMemoryController/FlexibleMemoryController.hpp"
#include "application/GpioPin/GpioPin.hpp"
#include "application/Math/Math.hpp"

#include <span>
#include <stdint.h>

namespace ATC {
struct Ws17143Pinout {
    GpioPin& lcdResetPin_;
};

class DisplayWs17143 {
private:
    static const uint16_t WIDTH_ = 480;
    static const uint16_t HEIGHT_ = 800;

    Ws17143Pinout& pinout_;
    FlexibleMemoryController& flexibleMemoryController_;
    DelayProvider& delayProvider_;

    void initResetLcdPin();
    void resetLcd();
    void initProprietaryHardwareSettings();
    void initProprietaryGammaSettings();
    void initRGB565Format();
    void exitSleepState();
    void enableDisplay();

public:
    DisplayWs17143(
        Ws17143Pinout& pinout,
        FlexibleMemoryController& flexibleMemoryController,
        DelayProvider& delayProvider
    );

    void init();
    void setWindow(const Rectangle& window);
    void drawTestPattern(const uint8_t colorOffset);
    void draw(const std::span<const uint16_t>& frameBuffer);
    void draw(
        const std::span<const uint16_t>& frameBuffer,
        const Rectangle& window
    );
};
}