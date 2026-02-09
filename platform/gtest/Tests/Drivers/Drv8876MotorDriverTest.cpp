#include "application/System/Drivers/MotorDriver/Drv8876MotorDriver/Drv8876MotorDriver.hpp"

#include "application/System/Ports/IGpioPin.hpp"
#include "platform/gtest/Mocks/Ports/GpioPinMock.hpp"
#include "platform/gtest/Mocks/Ports/PwmPinMock.hpp"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

using namespace testing;

namespace ATC {
class Drv8876MotorDriverTest : public Test {
public:
    GpioPinMock modePin_ {};
    PwmPinMock enablePin_ {};
    GpioPinMock phasePin_ {};
    GpioPinMock sleepPin_ {};
    GpioPinMock faultPin_ {};

    Drv8876MotorDriverPinout pinout_ {
        .modePin = modePin_,
        .enablePin = enablePin_,
        .phasePin = phasePin_,
        .sleepPin = sleepPin_,
        .faultPin = faultPin_
    };

    DRV8876MotorDriver drv8876MotorDriver_ {pinout_};
};

TEST_F(
    Drv8876MotorDriverTest,
    GIVEN_Drv8876MotorDriver_WHEN_driverIsInitialized_THEN_modePinIsSetUp
) {
    {
        InSequence sequence;
        EXPECT_CALL(modePin_, init(GpioMode::Output, GpioPull::NoPull));
        EXPECT_CALL(modePin_, setLow());
    }

    drv8876MotorDriver_.init();
}

TEST_F(
    Drv8876MotorDriverTest,
    GIVEN_Drv8876MotorDriver_WHEN_driverIsInitialized_THEN_enablePinIsSetUp
) {
    EXPECT_CALL(enablePin_, setDutyCycle(0));

    drv8876MotorDriver_.init();
}

TEST_F(
    Drv8876MotorDriverTest,
    GIVEN_Drv8876MotorDriver_WHEN_driverIsInitialized_THEN_phasePinIsSetUp
) {
    {
        InSequence sequence;
        EXPECT_CALL(phasePin_, init(GpioMode::Output, GpioPull::NoPull));
        EXPECT_CALL(phasePin_, setLow());
    }

    drv8876MotorDriver_.init();
}

TEST_F(
    Drv8876MotorDriverTest,
    GIVEN_Drv8876MotorDriver_WHEN_driverIsInitialized_THEN_sleepPinIsSetUp
) {
    {
        InSequence sequence;
        EXPECT_CALL(sleepPin_, init(GpioMode::Output, GpioPull::NoPull));
        EXPECT_CALL(sleepPin_, setLow());
    }

    drv8876MotorDriver_.init();
}

TEST_F(
    Drv8876MotorDriverTest,
    GIVEN_Drv8876MotorDriver_WHEN_driverIsInitialized_THEN_faultPinIsSetUp
) {
    EXPECT_CALL(faultPin_, init(GpioMode::Input, GpioPull::PullUp));

    drv8876MotorDriver_.init();
}

TEST_F(
    Drv8876MotorDriverTest,
    GIVEN_Drv8876MotorDriver_WHEN_startRotationIsCalled_THEN_driverIsEnabledWithDutyCycle
) {
    drv8876MotorDriver_.init();

    constexpr uint8_t speedPercent = 50;

    EXPECT_CALL(enablePin_, setDutyCycle(speedPercent));
    EXPECT_CALL(sleepPin_, setHigh());

    drv8876MotorDriver_.startRotation(speedPercent);
}

TEST_F(
    Drv8876MotorDriverTest,
    GIVEN_Drv8876MotorDriver_WHEN_stopRotationIsCalled_THEN_driverIsDisabled
) {
    drv8876MotorDriver_.init();

    EXPECT_CALL(enablePin_, setDutyCycle(0));
    EXPECT_CALL(sleepPin_, setLow());

    drv8876MotorDriver_.stopRotation();
}

TEST_F(
    Drv8876MotorDriverTest,
    GIVEN_Drv8876MotorDriver_WHEN_setDirectionClockwiseIsCalled_THEN_phasePinIsSet
) {
    drv8876MotorDriver_.init();

    EXPECT_CALL(phasePin_, setHigh());

    drv8876MotorDriver_.setDirectionClockwise();
}

TEST_F(
    Drv8876MotorDriverTest,
    GIVEN_Drv8876MotorDriver_WHEN_setDirectionCounterClockwiseIsCalled_THEN_phasePinIsSet
) {
    drv8876MotorDriver_.init();

    EXPECT_CALL(phasePin_, setLow());

    drv8876MotorDriver_.setDirectionCounterClockwise();
}

TEST_F(
    Drv8876MotorDriverTest,
    GIVEN_Drv8876MotorDriver_WHEN_isDirectionClockwiseIsCalled_THEN_phasePinStateIsReturned
) {
    drv8876MotorDriver_.init();

    ON_CALL(phasePin_, isLow()).WillByDefault(Return(false));
    ON_CALL(phasePin_, isHigh()).WillByDefault(Return(true));
    ASSERT_TRUE(drv8876MotorDriver_.isDirectionClockwise());

    ON_CALL(phasePin_, isLow()).WillByDefault(Return(true));
    ON_CALL(phasePin_, isHigh()).WillByDefault(Return(false));
    ASSERT_FALSE(drv8876MotorDriver_.isDirectionClockwise());
}

TEST_F(
    Drv8876MotorDriverTest,
    GIVEN_Drv8876MotorDriver_WHEN_isFaultDetectedCalled_THEN_faultPinStateIsReturned
) {
    drv8876MotorDriver_.init();

    ON_CALL(faultPin_, isLow()).WillByDefault(Return(false));
    ON_CALL(faultPin_, isHigh()).WillByDefault(Return(true));
    ASSERT_FALSE(drv8876MotorDriver_.isFaultDetected());

    ON_CALL(faultPin_, isLow()).WillByDefault(Return(true));
    ON_CALL(faultPin_, isHigh()).WillByDefault(Return(false));
    ASSERT_TRUE(drv8876MotorDriver_.isFaultDetected());
}
}
