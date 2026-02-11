#include "application/System/Drivers/StepperDriver/Tmc2226StepperDriver/Tmc2226StepperDriver.hpp"

#include "application/System/Ports/IGpioPin.hpp"
#include "platform/gtest/Mocks/Ports/AsyncPulsePinMock.hpp"
#include "platform/gtest/Mocks/Ports/GpioPinMock.hpp"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

using namespace testing;

namespace ATC {
class Tmc2226StepperDriverTest : public Test {
public:
    AsyncPulsePinMock stepPinMock_ {};
    GpioPinMock directionPinMock_ {};
    GpioPinMock diagnosticPinMock_ {};

    Tmc2226StepperDriverPinout pinout_ {
        .stepPin = stepPinMock_,
        .directionPin = directionPinMock_,
        .diagnosticPin = diagnosticPinMock_
    };
    Tmc2226StepperDriver tmc2226StepperDriver_ {pinout_};
};

TEST_F(
    Tmc2226StepperDriverTest,
    GIVEN_tmc2226StepperDriver_WHEN_driverIsInitialized_THEN_stepPinIsSetUp
) {
    InSequence sequence;

    EXPECT_CALL(stepPinMock_, init());
    EXPECT_CALL(stepPinMock_, disable());

    tmc2226StepperDriver_.init();
}

TEST_F(
    Tmc2226StepperDriverTest,
    GIVEN_tmc2226StepperDriver_WHEN_driverIsInitialized_THEN_directionPinIsSetUp
) {
    InSequence sequence;

    EXPECT_CALL(
        directionPinMock_, init(GpioMode::Output, GpioPull::NoPull)
    );
    EXPECT_CALL(directionPinMock_, setLow());

    tmc2226StepperDriver_.init();
}

TEST_F(
    Tmc2226StepperDriverTest,
    GIVEN_tmc2226StepperDriver_WHEN_driverIsInitialized_THEN_diagnosticPinIsSetUp
) {
    EXPECT_CALL(
        diagnosticPinMock_, init(GpioMode::Input, GpioPull::PullUp)
    );

    tmc2226StepperDriver_.init();
}

TEST_F(
    Tmc2226StepperDriverTest,
    GIVEN_tmc2226StepperDriver_WHEN_startSteppingIsCalled_THEN_stepPinIsEnabled
) {
    EXPECT_CALL(stepPinMock_, enable());

    tmc2226StepperDriver_.startStepping();
}

TEST_F(
    Tmc2226StepperDriverTest,
    GIVEN_tmc2226StepperDriver_WHEN_stopSteppingIsCalled_THEN_stepPinIsDisabled
) {
    EXPECT_CALL(stepPinMock_, disable());

    tmc2226StepperDriver_.stopStepping();
}

TEST_F(
    Tmc2226StepperDriverTest,
    GIVEN_tmc2226StepperDriver_WHEN_setMicrosecondsIsCalled_THEN_stepPinMicrosecondsAreSet
) {
    constexpr uint32_t microseconds = 200;

    EXPECT_CALL(stepPinMock_, setToggleMicroseconds(microseconds));

    tmc2226StepperDriver_.setMicrosecondsBetweenStepToggle(microseconds);
}

TEST_F(
    Tmc2226StepperDriverTest,
    GIVEN_tmc2226StepperDriver_WHEN_setDirectionClockwiseIsCalled_THEN_directionPinIsSetDown
) {
    EXPECT_CALL(directionPinMock_, setLow());

    tmc2226StepperDriver_.setDirectionClockwise();
}

TEST_F(
    Tmc2226StepperDriverTest,
    GIVEN_tmc2226StepperDriver_WHEN_setDirectionCounterClockwiseIsCalled_THEN_directionPinIsSetHigh
) {
    EXPECT_CALL(directionPinMock_, setHigh());

    tmc2226StepperDriver_.setDirectionCounterClockwise();
}

TEST_F(
    Tmc2226StepperDriverTest,
    GIVEN_tmc2226StepperDriver_WHEN_isFaultDetectedIsCalled_THEN_diagnosticPinStateIsReturned
) {
    ON_CALL(diagnosticPinMock_, isLow()).WillByDefault(Return(true));
    ON_CALL(diagnosticPinMock_, isHigh()).WillByDefault(Return(false));

    ASSERT_TRUE(tmc2226StepperDriver_.isFaultDetected());

    ON_CALL(diagnosticPinMock_, isLow()).WillByDefault(Return(false));
    ON_CALL(diagnosticPinMock_, isHigh()).WillByDefault(Return(true));

    ASSERT_FALSE(tmc2226StepperDriver_.isFaultDetected());
}
}
