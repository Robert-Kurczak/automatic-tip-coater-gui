#include "Ws17143Display.hpp"
#include "Ws17143ProprietarySettings.hpp"

namespace ATC {
static constexpr uint16_t RED_565_ = 0xF800;
static constexpr uint16_t GREEN_565_ = 0x07E0;
static constexpr uint16_t BLUE_565_ = 0x001F;

void Ws17143Display::setWindow(const Rectangle& window) {
    const std::array<uint8_t, 4> xBytes {
        uint8_t(window.xStart >> 8),
        uint8_t(window.xStart & 0xFF),
        uint8_t(window.xEnd >> 8),
        uint8_t(window.xEnd & 0xFF)
    };

    const std::array<uint8_t, 4> yBytes {
        uint8_t(window.yStart >> 8),
        uint8_t(window.yStart & 0xFF),
        uint8_t(window.yEnd >> 8),
        uint8_t(window.yEnd & 0xFF)
    };

    for (uint16_t i = 0; i < 4; i++) {
        flexibleMemoryController_.writeRegister(
            RegisterNumber {uint16_t(COLUMN_SET_REGISTER_.value + i)}
        );
        flexibleMemoryController_.writeData(Data {xBytes.at(i)});
    }

    for (uint8_t i = 0; i < 4; i++) {
        flexibleMemoryController_.writeRegister(
            RegisterNumber {uint16_t(ROW_SET_REGISTER_.value + i)}
        );
        flexibleMemoryController_.writeData(Data {yBytes.at(i)});
    }
}

void Ws17143Display::initResetLcdPin() {
    pinout_.lcdResetPin_.init(GpioMode::Output, GpioPull::NoPull);
}

void Ws17143Display::resetLcd() {
    constexpr uint8_t resetPulseMillis = 50;

    pinout_.lcdResetPin_.setLow();
    systemClock_.delayMilliseconds(resetPulseMillis);
    pinout_.lcdResetPin_.setHigh();
    systemClock_.delayMilliseconds(resetPulseMillis);
}

void Ws17143Display::initSettings() {
    for (const auto& instruction : PROPRIETARY_HARDWARE_SETTINGS_) {
        flexibleMemoryController_.write(instruction);
    }

    for (const auto& instruction : PROPRIETARY_GAMMA_SETTINGS_) {
        flexibleMemoryController_.write(instruction);
    }

    flexibleMemoryController_.write(RGB565_FORMAT_INSTRUCTION_);
}

void Ws17143Display::exitSleepState() {
    flexibleMemoryController_.write(EXIT_SLEEP_INSTRUCTION_);
    systemClock_.delayMilliseconds(DELAY_AFTER_SLEEP_MILLIS_);
}

void Ws17143Display::enableDisplay() {
    flexibleMemoryController_.write(ENABLE_DISPLAY_INSTRUCTION_);
    systemClock_.delayMilliseconds(DELAY_AFTER_ENABLE_MILLIS_);
}

void Ws17143Display::setAllPixelsOff() {
    flexibleMemoryController_.write(SET_PIXELS_OFF_INSTRUCTION_);
}

Ws17143Display::Ws17143Display(
    const Ws17143DisplayPinout& pinout,
    IFlexibleMemoryController& flexibleMemoryController,
    ISystemClock& systemClock
) :
    pinout_(pinout),
    flexibleMemoryController_(flexibleMemoryController),
    systemClock_(systemClock) {}

void Ws17143Display::init() {
    initResetLcdPin();
    resetLcd();
    initSettings();
    exitSleepState();
    enableDisplay();
    setAllPixelsOff();
}

void Ws17143Display::drawTestPattern(uint8_t seed) {
    setWindow(
        Rectangle {
            .xStart = 0,
            .xEnd = WIDTH_ - 1,
            .yStart = 0,
            .yEnd = HEIGHT_ - 1
        }
    );

    flexibleMemoryController_.writeRegister(MEMORY_WRITE_REGISTER_);

    for (uint16_t yIndex = 0; yIndex < HEIGHT_; yIndex++) {
        for (uint16_t xIndex = 0; xIndex < WIDTH_; xIndex++) {
            uint16_t color = BLUE_565_ - seed;

            if (yIndex < HEIGHT_ / 3) {
                color = RED_565_ + seed;
            } else if (yIndex < HEIGHT_ / 3 * 2) {
                color = GREEN_565_ / seed;
            }

            flexibleMemoryController_.writeData(Data {color});
        }
    }
}

void Ws17143Display::draw(
    const std::span<const uint16_t>& frameBuffer,
    const Rectangle& window
) {
    setWindow(window);

    flexibleMemoryController_.writeRegister(MEMORY_WRITE_REGISTER_);

    for (uint16_t yIndex = window.yStart; yIndex <= window.yEnd;
         yIndex++) {
        for (uint16_t xIndex = window.xStart; xIndex <= window.xEnd;
             xIndex++) {
            const uint16_t color =
                frameBuffer[(yIndex * WIDTH_) + xIndex];
            flexibleMemoryController_.writeData(Data {color});
        }
    }

    flexibleMemoryController_.write(NORMAL_DISPLAY_MODE_INSTRUCTION_);
}

void Ws17143Display::draw(const std::span<const uint16_t>& framebuffer) {
    constexpr Rectangle fullWindow {
        .xStart = 0, .xEnd = WIDTH_ - 1, .yStart = 0, .yEnd = HEIGHT_ - 1
    };

    draw(framebuffer, fullWindow);
}
}