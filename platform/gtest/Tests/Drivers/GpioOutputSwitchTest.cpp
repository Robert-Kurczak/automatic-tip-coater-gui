#include "application/System/Drivers/OutputSwitch/GpioOutputSwitch/GpioOutputSwitch.hpp"

#include "application/System/Drivers/Common/ActiveLevel.hpp"
#include "platform/gtest/Mocks/Ports/GpioPinMock.hpp"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

using namespace testing;

namespace ATC {
class GpioOutputSwitchTest : public Test {
public:
    GpioPinMock activeHighPinMock_ {};
    GpioPinMock activeLowPinMock_ {};

    GpioOutputSwitch<ActiveLevel::ActiveHigh> activeHighOutputSwitch_ {
        activeHighPinMock_
    };
    GpioOutputSwitch<ActiveLevel::ActiveLow> activeLowOutputSwitch_ {
        activeLowPinMock_
    };
};

TEST_F(
    GpioOutputSwitchTest,
    GIVEN_activeHighOutputSwitch_WHEN_switchIsInitialized_THEN_outputPinIsSetUp
) {
    EXPECT_CALL(
        activeHighPinMock_, init(GpioMode::Output, GpioPull::NoPull)
    );

    activeHighOutputSwitch_.init();
}

TEST_F(
    GpioOutputSwitchTest,
    GIVEN_activeLowOutputSwitch_WHEN_switchIsInitialized_THEN_outputPinIsSetUp
) {
    EXPECT_CALL(
        activeLowPinMock_, init(GpioMode::Output, GpioPull::NoPull)
    );

    activeLowOutputSwitch_.init();
}

TEST_F(
    GpioOutputSwitchTest,
    GIVEN_activeHighOutputSwitch_WHEN_turnOnIsCalled_THEN_outputPinIsSetHigh
) {
    activeHighOutputSwitch_.init();

    EXPECT_CALL(activeHighPinMock_, setHigh());

    activeHighOutputSwitch_.turnOn();
}

TEST_F(
    GpioOutputSwitchTest,
    GIVEN_activeLowOutputSwitch_WHEN_turnOnIsCalled_THEN_outputPinIsSetLow
) {
    activeLowOutputSwitch_.init();

    EXPECT_CALL(activeLowPinMock_, setLow());

    activeLowOutputSwitch_.turnOn();
}

TEST_F(
    GpioOutputSwitchTest,
    GIVEN_activeHighOutputSwitch_WHEN_turnOffIsCalled_THEN_outputPinIsSetLow
) {
    activeHighOutputSwitch_.init();

    EXPECT_CALL(activeHighPinMock_, setLow());

    activeHighOutputSwitch_.turnOff();
}

TEST_F(
    GpioOutputSwitchTest,
    GIVEN_activeLowOutputSwitch_WHEN_turnOffIsCalled_THEN_outputPinIsSetHigh
) {
    activeLowOutputSwitch_.init();

    EXPECT_CALL(activeLowPinMock_, setHigh());

    activeLowOutputSwitch_.turnOff();
}
}