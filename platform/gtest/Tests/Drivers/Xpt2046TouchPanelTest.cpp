#include "application/System/Drivers/ResistiveTouchPanel/Xpt2046TouchPanel/Xpt2046TouchPanel.hpp"

#include "application/System/Ports/IGpioPin.hpp"
#include "platform/gtest/Matchers/SpanMatcher.hpp"
#include "platform/gtest/Mocks/Controllers/LoggerSinkMock.hpp"
#include "platform/gtest/Mocks/Ports/GpioPinMock.hpp"
#include "platform/gtest/Mocks/Ports/SpiMock.hpp"

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <array>

using namespace testing;

namespace ATC {
class Xpt2046TouchPanelTest : public Test {
public:
    LoggerSinkMock loggerSinkMock_ {};

    GpioPinMock chipSelectPinMock_ {};
    GpioPinMock touchInterruptPinMock_ {};
    Xpt2046TouchPanelPinout pinout_ {
        .chipSelectPin = chipSelectPinMock_,
        .touchInterruptPin = touchInterruptPinMock_
    };

    SpiMock spiMock_ {};

    Xpt2046TouchPanel xpt2046TouchPanel_ {
        loggerSinkMock_,
        pinout_,
        spiMock_
    };

    struct ReadCommand {
        uint8_t value;
    };

    struct Expected12BitReating {
        uint16_t value;
    };

    void expectRawReading(
        ReadCommand readCommand,
        Expected12BitReating expected12BitReading
    ) {
        const std::array<uint8_t, 1> expectedSendData {readCommand.value};

        const uint16_t expected16BitReading = expected12BitReading.value
                                              << 4;
        const std::array<uint8_t, 2> expectedReceiveData {
            uint8_t(expected16BitReading >> 8),
            uint8_t(expected16BitReading & 0xFF)
        };

        {
            InSequence sequence;

            EXPECT_CALL(chipSelectPinMock_, setLow());
            EXPECT_CALL(
                spiMock_, sendData(SpanValueEq(expectedSendData))
            );
            EXPECT_CALL(spiMock_, receiveData(_))
                .WillOnce([expectedReceiveData](
                              std::span<uint8_t> outputBuffer
                          ) {
                    outputBuffer[0] = expectedReceiveData[0];
                    outputBuffer[1] = expectedReceiveData[1];
                });

            EXPECT_CALL(chipSelectPinMock_, setHigh());
        }
    }

    struct Z1Reading {
        uint16_t value;
    };
    struct Z2Reading {
        uint16_t value;
    };

    void expectPressureReading(
        Z1Reading expectedZ1Reading,
        Z2Reading expectedZ2Reading
    ) {
        {
            InSequence sequence {};
            expectRawReading(
                ReadCommand {ATC::Xpt2046TouchPanel::READ_Z1_COMMAND},
                Expected12BitReating {expectedZ1Reading.value}
            );

            expectRawReading(
                ReadCommand {ATC::Xpt2046TouchPanel::READ_Z2_COMMAND},
                Expected12BitReating {expectedZ2Reading.value}
            );
        }
    }
};

TEST_F(
    Xpt2046TouchPanelTest,
    GIVEN_xpt2046TouchPanel_WHEN_touchPanelIsInitialized_THEN_touchInterruptPinIsSetUp
) {
    EXPECT_CALL(
        touchInterruptPinMock_, init(GpioMode::Input, GpioPull::NoPull)
    );

    xpt2046TouchPanel_.init();
}

TEST_F(
    Xpt2046TouchPanelTest,
    GIVEN_xpt2046TouchPanel_WHEN_touchPanelIsInitialized_THEN_chipSelectPinIsSetUp
) {
    {
        InSequence sequence;

        EXPECT_CALL(
            chipSelectPinMock_, init(GpioMode::Output, GpioPull::NoPull)
        );

        EXPECT_CALL(chipSelectPinMock_, setHigh());
    }

    xpt2046TouchPanel_.init();
}

TEST_F(
    Xpt2046TouchPanelTest,
    GIVEN_xpt2046TouchPanel_WHEN_spiClockIsToFast_THEN_spiIsVerified
) {
    constexpr uint32_t tooFastClockInKilohertz = 2001;

    EXPECT_CALL(spiMock_, getSpeedInKilohertz())
        .WillRepeatedly(Return(tooFastClockInKilohertz));

    xpt2046TouchPanel_.init();

    ASSERT_THAT(loggerSinkMock_.buffer, HasSubstr("ERROR"));
}

TEST_F(
    Xpt2046TouchPanelTest,
    GIVEN_xpt2046TouchPanel_WHEN_spiClockIsSlowEnough_THEN_spiIsVerified
) {
    constexpr uint32_t correctFastClockInKilohertz = 1000;

    EXPECT_CALL(spiMock_, getSpeedInKilohertz())
        .WillRepeatedly(Return(correctFastClockInKilohertz));

    xpt2046TouchPanel_.init();

    ASSERT_THAT(loggerSinkMock_.buffer, Not(HasSubstr("ERROR")));
}

TEST_F(
    Xpt2046TouchPanelTest,
    GIVEN_xpt2046TouchPanel_WHEN_isTouchDetectedIsCalled_THEN_touchInterruptPinStateIsReturned
) {
    xpt2046TouchPanel_.init();

    ON_CALL(touchInterruptPinMock_, isHigh())
        .WillByDefault(Return(false));
    ON_CALL(touchInterruptPinMock_, isLow()).WillByDefault(Return(true));

    ASSERT_TRUE(xpt2046TouchPanel_.isTouchDetected());

    ON_CALL(touchInterruptPinMock_, isHigh()).WillByDefault(Return(true));
    ON_CALL(touchInterruptPinMock_, isLow()).WillByDefault(Return(false));

    ASSERT_FALSE(xpt2046TouchPanel_.isTouchDetected());
}

TEST_F(
    Xpt2046TouchPanelTest,
    GIVEN_xpt2046TouchPanel_WHEN_readRawXIsCalled_THEN_readXIsPerformedOverSpi
) {
    constexpr uint16_t expectedReading = 4000;

    xpt2046TouchPanel_.init();

    expectRawReading(
        ReadCommand {ATC::Xpt2046TouchPanel::READ_X_COMMAND},
        Expected12BitReating {expectedReading}
    );

    ASSERT_EQ(xpt2046TouchPanel_.readRawX(), expectedReading);
}

TEST_F(
    Xpt2046TouchPanelTest,
    GIVEN_xpt2046TouchPanel_WHEN_readRawYIsCalled_THEN_readYIsPerformedOverSpi
) {
    constexpr uint16_t expectedReading = 3000;

    xpt2046TouchPanel_.init();

    expectRawReading(
        ReadCommand {ATC::Xpt2046TouchPanel::READ_Y_COMMAND},
        Expected12BitReating {expectedReading}
    );

    ASSERT_EQ(xpt2046TouchPanel_.readRawY(), expectedReading);
}

TEST_F(
    Xpt2046TouchPanelTest,
    GIVEN_xpt2046TouchPanel_WHEN_readRawZIsCalled_THEN_readZIsPerformedOverSpi
) {
    constexpr uint16_t biggerReading = 2000;
    constexpr uint16_t lowerReading = 1000;

    xpt2046TouchPanel_.init();

    expectPressureReading(
        Z1Reading {biggerReading}, Z2Reading {lowerReading}
    );

    ASSERT_EQ(
        xpt2046TouchPanel_.readRawZ(), biggerReading - lowerReading
    );

    expectPressureReading(
        Z1Reading {lowerReading}, Z2Reading {biggerReading}
    );

    ASSERT_EQ(
        xpt2046TouchPanel_.readRawZ(), biggerReading - lowerReading
    );
}

TEST_F(
    Xpt2046TouchPanelTest,
    GIVEN_xpt2046TouchPanel_WHEN_readRawZIsCalledAndZ2IsGreaterThanZ1_THEN_readZIsPerformedOverSpi
) {
    constexpr uint16_t expectedZ1Reading = 1000;
    constexpr uint16_t expectedZ2Reading = 2000;

    xpt2046TouchPanel_.init();

    {
        InSequence sequence {};
        expectRawReading(
            ReadCommand {ATC::Xpt2046TouchPanel::READ_Z1_COMMAND},
            Expected12BitReating {expectedZ1Reading}
        );

        expectRawReading(
            ReadCommand {ATC::Xpt2046TouchPanel::READ_Z2_COMMAND},
            Expected12BitReating {expectedZ2Reading}
        );
    }

    ASSERT_EQ(
        xpt2046TouchPanel_.readRawZ(),
        expectedZ2Reading - expectedZ1Reading
    );
}
}
