#include "application/System/Services/AxisInterruptService/AxisInterruptService.hpp"

#include "platform/gtest/Mocks/Controllers/AxisMotionControllerMock.hpp"

#include "gtest/gtest.h"

using namespace testing;

namespace ATC {
class AxisInterruptServiceTest : public Test {
public:
    AxisMotionControllerMock axisMotionControllerMock_ {};

    AxisInterruptService axisInterruptService_ {
        axisMotionControllerMock_
    };
};

TEST_F(
    AxisInterruptServiceTest,
    GIVEN_axisInterruptService_WHEN_handleStepInterruptIsCalled_THEN_callIsForwardedToAxisMotionController
) {
    EXPECT_CALL(axisMotionControllerMock_, handleStepPulseInterrupt());

    axisInterruptService_.handleStepInterrupt();
}

TEST_F(
    AxisInterruptServiceTest,
    GIVEN_axisInterruptService_WHEN_handleMinLimitReachedInterruptIsCalled_THEN_callIsForwardedToAxisMotionController
) {
    EXPECT_CALL(
        axisMotionControllerMock_, handleMinLimitSwitchInterrupt()
    );

    axisInterruptService_.handleMinLimitReachedInterrupt();
}

TEST_F(
    AxisInterruptServiceTest,
    GIVEN_axisInterruptService_WHEN_handleMaxLimitReachedInterruptIsCalled_THEN_callIsForwardedToAxisMotionController
) {
    EXPECT_CALL(
        axisMotionControllerMock_, handleMaxLimitSwitchInterrupt()
    );

    axisInterruptService_.handleMaxLimitReachedInterrupt();
}
}