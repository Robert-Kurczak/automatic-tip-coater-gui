#include "application/System/Drivers/Display/Ws17143Display/Ws17143Display.hpp"

#include "application/System/Drivers/Display/Ws17143Display/Ws17143ProprietarySettings.hpp"
#include "application/System/Ports/IGpioPin.hpp"
#include "platform/gtest/Mocks/Controllers/FlexibleMemoryControllerMock.hpp"
#include "platform/gtest/Mocks/Ports/GpioPinMock.hpp"
#include "platform/gtest/Mocks/Ports/SystemClockMock.hpp"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

using namespace testing;

namespace ATC {
static constexpr uint8_t MIN_RESET_PULSE_MILLISECONDS = 10;
static constexpr uint8_t MIN_WAKE_PULSE_MILLISECONDS = 100;

class Ws17143DisplayTest : public Test {
protected:
    NiceMock<GpioPinMock> lcdResetPinMock_;
    NiceMock<FlexibleMemoryControllerMock> flexibleMemoryControllerMock_;
    NiceMock<SystemClockMock> systemClockMock_;
    Ws17143DisplayPinout pinout_ {.lcdResetPin_ = lcdResetPinMock_};

    Ws17143Display display_ {
        pinout_,
        flexibleMemoryControllerMock_,
        systemClockMock_
    };
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

        for (const auto& instruction : PROPRIETARY_HARDWARE_SETTINGS_) {
            EXPECT_CALL(flexibleMemoryControllerMock_, write(instruction))
                .RetiresOnSaturation();
        }

        for (const auto& instruction : PROPRIETARY_GAMMA_SETTINGS_) {
            EXPECT_CALL(flexibleMemoryControllerMock_, write(instruction))
                .RetiresOnSaturation();
        }

        EXPECT_CALL(
            flexibleMemoryControllerMock_,
            write(RGB565_FORMAT_INSTRUCTION_)
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
            write(RGB565_FORMAT_INSTRUCTION_)
        )
            .RetiresOnSaturation();
        EXPECT_CALL(
            flexibleMemoryControllerMock_, write(EXIT_SLEEP_INSTRUCTION_)
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
}