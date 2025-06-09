#pragma once

#include "application/DelayProvider/DelayProvider.hpp"
#include "application/FlexibleMemoryController/FlexibleMemoryController.hpp"
#include "application/GpioPin/GpioPin.hpp"

#include <span>
#include <stdint.h>

class DisplayWs17143 {
private:
    static const uint16_t WIDTH_ = 480;
    static const uint16_t HEIGHT_ = 800;

    FlexibleMemoryController& flexibleMemoryController_;
    GpioPin& lcdResetPin_;
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
        FlexibleMemoryController& flexibleMemoryController,
        GpioPin& lcdResetPin,
        DelayProvider& delayProvider
    );

    void init();
    void setWindow(
        const uint16_t startX,
        const uint16_t endX,
        const uint16_t startY,
        const uint16_t endY
    );
    void drawTestPattern(const uint8_t colorOffset);
    void draw(const std::span<const uint16_t>& frameBuffer);
    void draw(
        const std::span<const uint16_t>& frameBuffer,
        const uint16_t xStart,
        const uint16_t xEnd,
        const uint16_t yStart,
        const uint16_t yEnd
    );
};