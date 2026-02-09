#include "application/System/Drivers/Display/Ws17143Display/Ws17143Display.hpp"

#include "application/System/Drivers/Display/Ws17143Display/Ws17143ProprietarySettings.hpp"
#include "application/Utils/Math.hpp"
#include "platform/gtest/Mocks/Controllers/FlexibleMemoryControllerMock.hpp"
#include "platform/gtest/Mocks/Ports/GpioPinMock.hpp"
#include "platform/gtest/Mocks/Ports/SystemClockMock.hpp"

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <array>
#include <cstddef>

using namespace testing;

namespace ATC {
static constexpr uint8_t MIN_RESET_PULSE_MILLISECONDS = 10;
static constexpr uint8_t MIN_WAKE_PULSE_MILLISECONDS = 100;
static constexpr uint8_t MIN_SCREEN_ENABLE_PULSE_MILLISECONDS = 10;

class Ws17143DisplayTest : public Test {
public:
    NiceMock<GpioPinMock> lcdResetPinMock_;
    NiceMock<FlexibleMemoryControllerMock> flexibleMemoryControllerMock_;
    NiceMock<SystemClockMock> systemClockMock_;
    Ws17143DisplayPinout pinout_ {.lcdResetPin_ = lcdResetPinMock_};

    Ws17143Display display_ {
        pinout_,
        flexibleMemoryControllerMock_,
        systemClockMock_
    };

    void expectSetColumnCursor(const Rectangle& window) {
        EXPECT_CALL(
            flexibleMemoryControllerMock_,
            writeRegister(COLUMN_SET_REGISTER)
        )
            .RetiresOnSaturation();

        EXPECT_CALL(
            flexibleMemoryControllerMock_,
            writeData(Data {uint16_t(window.xStart >> 8)})
        )
            .RetiresOnSaturation();

        EXPECT_CALL(
            flexibleMemoryControllerMock_,
            writeRegister(RegisterNumber {COLUMN_SET_REGISTER.value + 1})
        )
            .RetiresOnSaturation();

        EXPECT_CALL(
            flexibleMemoryControllerMock_,
            writeData(Data {uint16_t(window.xStart & 0xFF)})
        )
            .RetiresOnSaturation();

        EXPECT_CALL(
            flexibleMemoryControllerMock_,
            writeRegister(RegisterNumber {COLUMN_SET_REGISTER.value + 2})
        )
            .RetiresOnSaturation();

        EXPECT_CALL(
            flexibleMemoryControllerMock_,
            writeData(Data {uint16_t(window.xEnd >> 8)})
        )
            .RetiresOnSaturation();

        EXPECT_CALL(
            flexibleMemoryControllerMock_,
            writeRegister(RegisterNumber {COLUMN_SET_REGISTER.value + 3})
        )
            .RetiresOnSaturation();

        EXPECT_CALL(
            flexibleMemoryControllerMock_,
            writeData(Data {uint16_t(window.xEnd & 0xFF)})
        )
            .RetiresOnSaturation();
    }

    void expectSetRowCursor(const Rectangle& window) {
        EXPECT_CALL(
            flexibleMemoryControllerMock_,
            writeRegister(ROW_SET_REGISTER)
        )
            .RetiresOnSaturation();

        EXPECT_CALL(
            flexibleMemoryControllerMock_,
            writeData(Data {uint16_t(window.yStart >> 8)})
        )
            .RetiresOnSaturation();

        EXPECT_CALL(
            flexibleMemoryControllerMock_,
            writeRegister(RegisterNumber {ROW_SET_REGISTER.value + 1})
        )
            .RetiresOnSaturation();

        EXPECT_CALL(
            flexibleMemoryControllerMock_,
            writeData(Data {uint16_t(window.yStart & 0xFF)})
        )
            .RetiresOnSaturation();

        EXPECT_CALL(
            flexibleMemoryControllerMock_,
            writeRegister(RegisterNumber {ROW_SET_REGISTER.value + 2})
        )
            .RetiresOnSaturation();

        EXPECT_CALL(
            flexibleMemoryControllerMock_,
            writeData(Data {uint16_t(window.yEnd >> 8)})
        )
            .RetiresOnSaturation();

        EXPECT_CALL(
            flexibleMemoryControllerMock_,
            writeRegister(RegisterNumber {ROW_SET_REGISTER.value + 3})
        )
            .RetiresOnSaturation();

        EXPECT_CALL(
            flexibleMemoryControllerMock_,
            writeData(Data {uint16_t(window.yEnd & 0xFF)})
        )
            .RetiresOnSaturation();
    }

    void expectSetWindow(const Rectangle& window) {
        expectSetColumnCursor(window);
        expectSetRowCursor(window);
    }
};

TEST_F(
    Ws17143DisplayTest,
    GIVEN_Ws17143Display_WHEN_displayIsInitialized_THEN_resetPinIsSetUp
) {
    EXPECT_CALL(
        lcdResetPinMock_, init(GpioMode::Output, GpioPull::NoPull)
    );

    display_.init();
}

TEST_F(
    Ws17143DisplayTest,
    GIVEN_Ws17413Display_WHEN_resetPinIsSetUp_THEN_displayIsReset
) {
    EXPECT_CALL(systemClockMock_, delayMilliseconds).Times(AnyNumber());

    {
        InSequence sequence {};

        EXPECT_CALL(lcdResetPinMock_, init(_, _));

        EXPECT_CALL(lcdResetPinMock_, setLow());
        EXPECT_CALL(
            systemClockMock_,
            delayMilliseconds(Ge(MIN_RESET_PULSE_MILLISECONDS))
        )
            .RetiresOnSaturation();
        EXPECT_CALL(lcdResetPinMock_, setHigh());
        EXPECT_CALL(
            systemClockMock_,
            delayMilliseconds(Ge(MIN_RESET_PULSE_MILLISECONDS))
        )
            .RetiresOnSaturation();
    }

    display_.init();
}

TEST_F(
    Ws17143DisplayTest,
    GIVEN_Ws17143Display_WHEN_displayIsReset_THEN_proprietarySettingsAreSetUp
) {
    EXPECT_CALL(flexibleMemoryControllerMock_, write).Times(AnyNumber());

    {
        InSequence sequence {};

        for (const auto& instruction : PROPRIETARY_HARDWARE_SETTINGS) {
            EXPECT_CALL(flexibleMemoryControllerMock_, write(instruction))
                .RetiresOnSaturation();
        }

        for (const auto& instruction : PROPRIETARY_GAMMA_SETTINGS) {
            EXPECT_CALL(flexibleMemoryControllerMock_, write(instruction))
                .RetiresOnSaturation();
        }

        EXPECT_CALL(
            flexibleMemoryControllerMock_,
            write(RGB565_FORMAT_INSTRUCTION)
        )
            .RetiresOnSaturation();
    }

    display_.init();
}

TEST_F(
    Ws17143DisplayTest,
    GIVEN_Ws17143Display_WHEN_proprietarySettingsAreSetUp_THEN_displayIsWokenUp
) {
    EXPECT_CALL(flexibleMemoryControllerMock_, write).Times(AnyNumber());
    EXPECT_CALL(systemClockMock_, delayMilliseconds).Times(AnyNumber());

    {
        InSequence sequence;
        EXPECT_CALL(
            flexibleMemoryControllerMock_,
            write(RGB565_FORMAT_INSTRUCTION)
        )
            .RetiresOnSaturation();
        EXPECT_CALL(
            flexibleMemoryControllerMock_, write(EXIT_SLEEP_INSTRUCTION)
        )
            .RetiresOnSaturation();
        EXPECT_CALL(
            systemClockMock_,
            delayMilliseconds(Ge(MIN_WAKE_PULSE_MILLISECONDS))
        )
            .RetiresOnSaturation();
    }

    display_.init();
}

TEST_F(
    Ws17143DisplayTest,
    GIVEN_Ws17413Display_WHEN_displayIsWoken_THEN_screenIsEnabled
) {
    EXPECT_CALL(flexibleMemoryControllerMock_, write).Times(AnyNumber());
    EXPECT_CALL(systemClockMock_, delayMilliseconds).Times(AnyNumber());

    {
        InSequence sequence;

        EXPECT_CALL(
            flexibleMemoryControllerMock_, write(EXIT_SLEEP_INSTRUCTION)
        )
            .RetiresOnSaturation();
        EXPECT_CALL(
            flexibleMemoryControllerMock_,
            write(ENABLE_DISPLAY_INSTRUCTION)
        )
            .RetiresOnSaturation();
        EXPECT_CALL(
            systemClockMock_,
            delayMilliseconds(Ge(MIN_SCREEN_ENABLE_PULSE_MILLISECONDS))
        )
            .RetiresOnSaturation();
    }

    display_.init();
}

TEST_F(
    Ws17143DisplayTest,
    GIVEN_Ws17413Display_WHEN_screenIsEnabled_THEN_pixelsAreSetOff
) {
    EXPECT_CALL(flexibleMemoryControllerMock_, write).Times(AnyNumber());
    EXPECT_CALL(systemClockMock_, delayMilliseconds).Times(AnyNumber());

    {
        InSequence sequence;

        EXPECT_CALL(
            flexibleMemoryControllerMock_,
            write(ENABLE_DISPLAY_INSTRUCTION)
        )
            .RetiresOnSaturation();
        EXPECT_CALL(
            flexibleMemoryControllerMock_,
            write(SET_PIXELS_OFF_INSTRUCTION)
        )
            .RetiresOnSaturation();
    }

    display_.init();
}

TEST_F(
    Ws17143DisplayTest,
    GIVEN_Ws17413Display_WHEN_drawTestPatternIsCalled_THEN_patternIsDrawn
) {
    EXPECT_CALL(flexibleMemoryControllerMock_, write).Times(AnyNumber());
    EXPECT_CALL(systemClockMock_, delayMilliseconds).Times(AnyNumber());

    {
        InSequence sequence;

        expectSetWindow(
            Rectangle {
                .xStart = 0,
                .xEnd = ATC::Ws17143Display::WIDTH_ - 1,
                .yStart = 0,
                .yEnd = ATC::Ws17143Display::HEIGHT_ - 1
            }
        );

        EXPECT_CALL(
            flexibleMemoryControllerMock_,
            writeRegister(MEMORY_WRITE_REGISTER)
        )
            .RetiresOnSaturation();

        EXPECT_CALL(flexibleMemoryControllerMock_, writeData)
            .Times(
                (ATC::Ws17143Display::WIDTH_) *
                (ATC::Ws17143Display::HEIGHT_)
            );
    }

    display_.init();
    display_.drawTestPattern(0);
}

TEST_F(
    Ws17143DisplayTest,
    GIVEN_Ws17413Display_WHEN_drawIsCalledWithSpecifiedWindow_THEN_framebufferIsDrawnOnWindow
) {
    EXPECT_CALL(flexibleMemoryControllerMock_, write).Times(AnyNumber());
    EXPECT_CALL(systemClockMock_, delayMilliseconds).Times(AnyNumber());
    display_.init();

    const std::array<uint16_t, 4> framebuffer {0, 1, 2, 3};
    const Rectangle window {
        .xStart = 0,
        .xEnd = framebuffer.size() - 1,
        .yStart = 0,
        .yEnd = 0
    };

    {
        InSequence sequence;

        expectSetWindow(window);

        EXPECT_CALL(
            flexibleMemoryControllerMock_,
            writeRegister(MEMORY_WRITE_REGISTER)
        );

        for (uint16_t pixel : framebuffer) {
            EXPECT_CALL(
                flexibleMemoryControllerMock_, writeData(Data {pixel})
            );
        }

        EXPECT_CALL(
            flexibleMemoryControllerMock_,
            write(NORMAL_DISPLAY_MODE_INSTRUCTION)
        );
    }

    display_.draw(framebuffer, window);
}

TEST_F(
    Ws17143DisplayTest,
    GIVEN_Ws17413Display_WHEN_drawIsCalledWithoutSpecifiedWindow_THEN_framebufferIsDrawnOnWholeScreen
) {
    EXPECT_CALL(flexibleMemoryControllerMock_, write).Times(AnyNumber());
    EXPECT_CALL(systemClockMock_, delayMilliseconds).Times(AnyNumber());
    display_.init();

    const uint16_t expectedPixel = 585;
    const auto framebufferSize = size_t(
        ATC::Ws17143Display::WIDTH_ * ATC::Ws17143Display::HEIGHT_
    );

    std::array<uint16_t, framebufferSize> framebuffer {};
    framebuffer.fill(expectedPixel);

    const Rectangle expectedWindow {
        .xStart = 0,
        .xEnd = ATC::Ws17143Display::WIDTH_ - 1,
        .yStart = 0,
        .yEnd = ATC::Ws17143Display::HEIGHT_ - 1
    };

    {
        InSequence sequence;
        expectSetWindow(expectedWindow);

        EXPECT_CALL(
            flexibleMemoryControllerMock_,
            writeRegister(MEMORY_WRITE_REGISTER)
        );

        EXPECT_CALL(
            flexibleMemoryControllerMock_, writeData(Data {expectedPixel})
        )
            .Times(framebuffer.size());

        EXPECT_CALL(
            flexibleMemoryControllerMock_,
            write(NORMAL_DISPLAY_MODE_INSTRUCTION)
        );
    }

    display_.draw(framebuffer);
}
}