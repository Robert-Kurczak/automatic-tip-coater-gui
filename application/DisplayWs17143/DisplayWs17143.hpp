#pragma once

#include "application/DelayProvider/DelayProvider.hpp"
#include "application/FlexibleMemoryController/FlexibleMemoryController.hpp"

#include <stdint.h>
#include <span>

class DisplayWs17143 {
private:
    static const uint16_t WIDTH = 480;
    static const uint16_t HEIGHT = 800;

    FlexibleMemoryController& flexibleMemoryController;
    DelayProvider& delayProvider;

    void initProprietaryHardwareSettings();
    void initProprietaryGammaSettings();
    void initRGB565Format();
    void exitSleepState();
    void enableDisplay();

public:
    DisplayWs17143(
        FlexibleMemoryController& flexibleMemoryController_,
        DelayProvider& delayProvider_
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
};