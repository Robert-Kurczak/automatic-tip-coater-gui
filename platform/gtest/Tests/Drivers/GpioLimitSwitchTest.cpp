#include "application/System/Drivers/LimitSwitch/GpioLimitSwitch/GpioLimitSwitch.hpp"

#include "application/System/Drivers/Common/ActiveLevel.hpp"
#include "platform/gtest/Mocks/Ports/GpioPinMock.hpp"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

using namespace testing;

namespace ATC {
class GpioLimitSwitchTest : public Test {
public:
    GpioPinMock activeHighGpioPinMock_ {};
    GpioPinMock activeLowGpioPinMock_ {};

    GpioLimitSwitch<ActiveLevel::ActiveHigh> activeHighLimitSwitch_ {
        activeHighGpioPinMock_
    };
    GpioLimitSwitch<ActiveLevel::ActiveLow> activeLowLimitSwitch_ {
        activeLowGpioPinMock_
    };
};

TEST_F(
    GpioLimitSwitchTest,
    GIVEN_activeHighLimitSwitch_WHEN_switchIsInitialized_THEN_inputPinIsSetUp
) {
    EXPECT_CALL(
        activeHighGpioPinMock_,
        init(GpioMode::InterruptOnFallingEdge, GpioPull::PullUp)
    );

    activeHighLimitSwitch_.init();
}

TEST_F(
    GpioLimitSwitchTest,
    GIVEN_activeLowLimitSwitch_WHEN_switchIsInitialized_THEN_inputPinIsSetUp
) {
    EXPECT_CALL(
        activeLowGpioPinMock_,
        init(GpioMode::InterruptOnRisingEdge, GpioPull::PullDown)

    );

    activeLowLimitSwitch_.init();
}

TEST_F(
    GpioLimitSwitchTest,
    GIVEN_activeHighLimitSwitch_WHEN_isActiveIsCalled_THEN_pinStateIsReturned
) {
    ON_CALL(activeHighGpioPinMock_, isHigh()).WillByDefault(Return(true));
    ON_CALL(activeHighGpioPinMock_, isLow()).WillByDefault(Return(false));

    ASSERT_TRUE(activeHighLimitSwitch_.isActive());

    ON_CALL(activeHighGpioPinMock_, isHigh())
        .WillByDefault(Return(false));
    ON_CALL(activeHighGpioPinMock_, isLow()).WillByDefault(Return(true));

    ASSERT_FALSE(activeHighLimitSwitch_.isActive());
}

TEST_F(
    GpioLimitSwitchTest,
    GIVEN_activeLowLimitSwitch_WHEN_isActiveIsCalled_THEN_pinStateIsReturned
) {
    ON_CALL(activeLowGpioPinMock_, isHigh()).WillByDefault(Return(false));
    ON_CALL(activeLowGpioPinMock_, isLow()).WillByDefault(Return(true));

    ASSERT_TRUE(activeLowLimitSwitch_.isActive());

    ON_CALL(activeLowGpioPinMock_, isHigh()).WillByDefault(Return(true));
    ON_CALL(activeLowGpioPinMock_, isLow()).WillByDefault(Return(false));

    ASSERT_FALSE(activeLowLimitSwitch_.isActive());
}
}