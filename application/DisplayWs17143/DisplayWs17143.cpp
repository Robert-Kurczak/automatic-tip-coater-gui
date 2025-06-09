#include "DisplayWs17143.hpp"

#include <array>

// TODO add rgb to rgb565 conversion
// TODO remove visible noise on bootup

namespace ATC {

void DisplayWs17143::initResetLcdPin() {
    pinout_.lcdResetPin_.setOutputMode();
}

void DisplayWs17143::resetLcd() {
    pinout_.lcdResetPin_.setLow();
    delayProvider_.delayMiliseconds(50);
    pinout_.lcdResetPin_.setHigh();
    delayProvider_.delayMiliseconds(50);
}

void DisplayWs17143::initProprietaryHardwareSettings() {
    // Manufacturer Page 1 Commands Enable
    flexibleMemoryController_.write(0xF000, 0x50);
    flexibleMemoryController_.write(0xF001, 0xAA);
    flexibleMemoryController_.write(0xF002, 0x52);
    flexibleMemoryController_.write(0xF003, 0x08);
    flexibleMemoryController_.write(0xF004, 0x01);
    // AVDD: 5.2V
    flexibleMemoryController_.write(0xB000, 0x0D);
    flexibleMemoryController_.write(0xB001, 0x0D);
    flexibleMemoryController_.write(0xB002, 0x0D);
    // AVEE: -5.2V
    flexibleMemoryController_.write(0xB100, 0x0D);
    flexibleMemoryController_.write(0xB101, 0x0D);
    flexibleMemoryController_.write(0xB102, 0x0D);
    // VCL: -2.5V
    flexibleMemoryController_.write(0xB200, 0x00);
    flexibleMemoryController_.write(0xB201, 0x00);
    flexibleMemoryController_.write(0xB202, 0x00);
    // VGH: 15V
    flexibleMemoryController_.write(0xB300, 0x05);
    flexibleMemoryController_.write(0xB301, 0x05);
    flexibleMemoryController_.write(0xB302, 0x05);
    // VGL: -10V
    flexibleMemoryController_.write(0xB500, 0x28);
    flexibleMemoryController_.write(0xB501, 0x28);
    flexibleMemoryController_.write(0xB502, 0x28);
    // VCOM: -1.375V
    flexibleMemoryController_.write(0xB600, 0x05);
    flexibleMemoryController_.write(0xB601, 0x05);
    flexibleMemoryController_.write(0xB602, 0x05);
}

void DisplayWs17143::initProprietaryGammaSettings() {
    flexibleMemoryController_.write(0xD100, 0x00);
    flexibleMemoryController_.write(0xD101, 0x00);
    flexibleMemoryController_.write(0xD102, 0x00);
    flexibleMemoryController_.write(0xD103, 0x00);
    flexibleMemoryController_.write(0xD104, 0x00);
    flexibleMemoryController_.write(0xD105, 0x00);
    flexibleMemoryController_.write(0xD106, 0x00);
    flexibleMemoryController_.write(0xD107, 0x00);
    flexibleMemoryController_.write(0xD108, 0x00);
    flexibleMemoryController_.write(0xD109, 0x00);
    flexibleMemoryController_.write(0xD10A, 0x00);
    flexibleMemoryController_.write(0xD10B, 0x00);
    flexibleMemoryController_.write(0xD10C, 0x00);
    flexibleMemoryController_.write(0xD10D, 0x00);
    flexibleMemoryController_.write(0xD10E, 0x00);
    flexibleMemoryController_.write(0xD10F, 0x00);
}

void DisplayWs17143::initRGB565Format() {
    flexibleMemoryController_.write(0x3A00, 0x55);
}

void DisplayWs17143::exitSleepState() {
    flexibleMemoryController_.write(0x1100, 0x00);
    delayProvider_.delayMiliseconds(120);
}

void DisplayWs17143::enableDisplay() {
    flexibleMemoryController_.write(0x2900, 0x00);
    delayProvider_.delayMiliseconds(10);
}

DisplayWs17143::DisplayWs17143(
    Ws17143Pinout& pinout,
    FlexibleMemoryController& flexibleMemoryController,
    DelayProvider& delayProvider
) :
    pinout_(pinout),
    flexibleMemoryController_(flexibleMemoryController),
    delayProvider_(delayProvider) {}

void DisplayWs17143::init() {
    initResetLcdPin();
    resetLcd();

    initProprietaryHardwareSettings();
    initProprietaryGammaSettings();
    initRGB565Format();
    exitSleepState();
    enableDisplay();
}

void DisplayWs17143::setWindow(const Rectangle& window) {
    const uint8_t xBytes[] {
        uint8_t(window.xStart_ >> 8),
        uint8_t(window.xStart_ & 0xFF),
        uint8_t(window.xEnd_ >> 8),
        uint8_t(window.xEnd_ & 0xFF)
    };
    const uint8_t yBytes[] {
        uint8_t(window.yStart_ >> 8),
        uint8_t(window.yStart_ & 0xFF),
        uint8_t(window.yEnd_ >> 8),
        uint8_t(window.yEnd_ & 0xFF)
    };

    for (uint8_t i = 0; i < 4; i++) {
        flexibleMemoryController_.write(0x2A00 + i, xBytes[i]);
    }

    for (uint8_t i = 0; i < 4; i++) {
        flexibleMemoryController_.write(0x2B00 + i, yBytes[i]);
    }
}

void DisplayWs17143::drawTestPattern(const uint8_t colorOffset) {
    setWindow(
        Rectangle {
            .xStart_ = 0,
            .xEnd_ = WIDTH_ - 1,
            .yStart_ = 0,
            .yEnd_ = HEIGHT_ - 1
        }
    );

    flexibleMemoryController_.writeRegister(0x2C00);
    // TODO test is this delay really neccessary
    // It's a lot
    delayProvider_.delayMiliseconds(150);

    for (uint16_t y = 0; y < HEIGHT_; y++) {
        for (uint16_t x = 0; x < WIDTH_; x++) {
            uint16_t color;
            if (y < HEIGHT_ / 3) {
                color = 0xF800 + colorOffset; // red
            } else if (y < HEIGHT_ / 3 * 2) {
                color = 0x07E0 / colorOffset; // green
            } else {
                color = 0x001F - colorOffset; // blue
            }
            flexibleMemoryController_.writeData(color);
        }
    }
}

void DisplayWs17143::draw(const std::span<const uint16_t>& frameBuffer) {
    setWindow(
        Rectangle {
            .xStart_ = 0,
            .xEnd_ = WIDTH_ - 1,
            .yStart_ = 0,
            .yEnd_ = HEIGHT_ - 1
        }
    );

    flexibleMemoryController_.writeRegister(0x2C00);

    for (uint16_t y = 0; y < HEIGHT_; y++) {
        for (uint16_t x = 0; x < WIDTH_; x++) {
            const uint16_t color = frameBuffer[y * WIDTH_ + x];
            flexibleMemoryController_.writeData(color);
        }
    }
}

void DisplayWs17143::draw(
    const std::span<const uint16_t>& frameBuffer,
    const Rectangle& window
) {
    setWindow(window);

    flexibleMemoryController_.writeRegister(0x2C00);

    for (uint16_t y = window.yStart_; y <= window.yEnd_; y++) {
        for (uint16_t x = window.xStart_; x <= window.xEnd_; x++) {
            const uint16_t color = frameBuffer[y * WIDTH_ + x];
            flexibleMemoryController_.writeData(color);
        }
    }
}
}