#include "application/System/Controllers/AxisMotionController/AxisMotionController.hpp"

#include "application/System/Controllers/AxisMotionController/AxisMotionParameters.hpp"
#include "platform/gtest/Mocks/Controllers/LoggerSinkMock.hpp"
#include "platform/gtest/Mocks/Drivers/LimitSwitchMock.hpp"
#include "platform/gtest/Mocks/Drivers/StepperDriverMock.hpp"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

using namespace testing;

namespace ATC {
class AxisMotionControllerTest : public Test {
public:
    static constexpr uint32_t MICROSECONDS_IN_SECOND = 1'000'000;
    static constexpr uint32_t MICROMETERS_IN_MILLIMETER = 1'000;

    static constexpr uint32_t VALID_MILLIMETERS_PER_SECOND =
        (AxisMotionController::MIN_MILLIMETERS_PER_SECOND +
         AxisMotionController::MAX_MILLIMETERS_PER_SECOND) /
        2;

    static constexpr uint32_t TOO_SMALL_MILLIMETERS_PER_SECOND =
        AxisMotionController::MIN_MILLIMETERS_PER_SECOND - 1;

    static constexpr uint32_t TOO_BIG_MILLIMETERS_PER_SECOND =
        AxisMotionController::MAX_MILLIMETERS_PER_SECOND + 1;

    static constexpr uint32_t POSITION_TOLERANCE_IN_MICROMETERS = 5;

    static constexpr AxisMotionParameters
        AXIS_MOTION_PARAMETERS_CLOCKWISE_FORWARD {
            .millimetersPerRotation = 5,
            .motorStepsPerRotation = 200,
            .driverStepDivider = 16,
            .isClockwiseRotationForwardMovement = true,
            .stepErrorMargin = 2
        };

    static constexpr AxisMotionParameters
        AXIS_MOTION_PARAMETERS_COUNTERCLOCKWISE_FORWARD {
            .millimetersPerRotation = 5,
            .motorStepsPerRotation = 200,
            .driverStepDivider = 16,
            .isClockwiseRotationForwardMovement = false,
            .stepErrorMargin = 2
        };

    uint32_t calculateMicrosecondsBetweenSteps(
        uint32_t millimetersPerSecond
    ) {
        const uint32_t totalStepsPerRotation =
            AXIS_MOTION_PARAMETERS_CLOCKWISE_FORWARD
                .motorStepsPerRotation *
            AXIS_MOTION_PARAMETERS_CLOCKWISE_FORWARD.driverStepDivider;

        return (MICROSECONDS_IN_SECOND *
                AXIS_MOTION_PARAMETERS_CLOCKWISE_FORWARD
                    .millimetersPerRotation) /
               (totalStepsPerRotation * millimetersPerSecond);
    }

    uint32_t convertMicrometersToSteps(uint32_t micrometers) {
        const uint32_t stepsPerMillimeter =
            AXIS_MOTION_PARAMETERS_CLOCKWISE_FORWARD
                .motorStepsPerRotation *
            AXIS_MOTION_PARAMETERS_CLOCKWISE_FORWARD.driverStepDivider /
            AXIS_MOTION_PARAMETERS_CLOCKWISE_FORWARD
                .millimetersPerRotation;

        return (micrometers * stepsPerMillimeter) /
               MICROMETERS_IN_MILLIMETER;
    }

    uint32_t convertStepsToMicrometers(uint32_t steps) const {
        const uint32_t nominator =
            steps * MICROMETERS_IN_MILLIMETER *
            AXIS_MOTION_PARAMETERS_CLOCKWISE_FORWARD
                .millimetersPerRotation;

        const uint32_t denominator =
            AXIS_MOTION_PARAMETERS_CLOCKWISE_FORWARD
                .motorStepsPerRotation *
            AXIS_MOTION_PARAMETERS_CLOCKWISE_FORWARD.driverStepDivider;

        return nominator / denominator;
    }

    NiceMock<LoggerSinkMock> loggerSinkMock_;
    NiceMock<StepperDriverMock> stepperDriverMock_;
    NiceMock<LimitSwitchMock> minLimitSwitchMock_;
    NiceMock<LimitSwitchMock> maxLimitSwitchMock_;
    LimitSwitchPair limitSwitchPair_ {
        .minLimitSwitch = minLimitSwitchMock_,
        .maxLimitSwitch = maxLimitSwitchMock_
    };

    AxisMotionController axisMotionController_ {
        loggerSinkMock_,
        stepperDriverMock_,
        limitSwitchPair_,
        AXIS_MOTION_PARAMETERS_CLOCKWISE_FORWARD
    };
};

TEST_F(
    AxisMotionControllerTest,
    GIVEN_axisMotionController_WHEN_controllerIsInitialized_THEN_stepperDriverIsInitialized
) {
    {
        InSequence sequence;

        EXPECT_CALL(stepperDriverMock_, init());
        EXPECT_CALL(stepperDriverMock_, stopStepping());
    }

    axisMotionController_.init();
}

TEST_F(
    AxisMotionControllerTest,
    GIVEN_axisMotionController_WHEN_minLimitSwitchInterruptOccurs_THEN_controllerStopsStepping
) {
    EXPECT_CALL(stepperDriverMock_, stopStepping());

    axisMotionController_.handleMinLimitSwitchInterrupt();
}

TEST_F(
    AxisMotionControllerTest,
    GIVEN_axisMotionController_WHEN_maxLimitSwitchInterruptOccurs_THEN_controllerStopsStepping
) {
    EXPECT_CALL(stepperDriverMock_, stopStepping());

    axisMotionController_.handleMaxLimitSwitchInterrupt();
}

TEST_F(
    AxisMotionControllerTest,
    GIVEN_axisMotionController_WHEN_setMillimetersPerSecondIsCalled_THEN_stepperDriverToggleMicrosecondsAreSet
) {
    const uint32_t expectedToggleMicroseconds =
        calculateMicrosecondsBetweenSteps(VALID_MILLIMETERS_PER_SECOND);

    EXPECT_CALL(
        stepperDriverMock_,
        setMicrosecondsBetweenStepToggle(expectedToggleMicroseconds)
    );

    axisMotionController_.setMillimetersPerSecond(
        VALID_MILLIMETERS_PER_SECOND
    );
}

TEST_F(
    AxisMotionControllerTest,
    GIVEN_axisMotionController_WHEN_setMillimetersPerSecondIsCalledWithTooBigValue_THEN_stepperDriverClampedToggleMicrosecondsAreSet
) {
    const uint32_t expectedToggleMicroseconds =
        calculateMicrosecondsBetweenSteps(
            AxisMotionController::MAX_MILLIMETERS_PER_SECOND
        );

    EXPECT_CALL(
        stepperDriverMock_,
        setMicrosecondsBetweenStepToggle(expectedToggleMicroseconds)
    );

    axisMotionController_.setMillimetersPerSecond(
        TOO_BIG_MILLIMETERS_PER_SECOND
    );
}

TEST_F(
    AxisMotionControllerTest,
    GIVEN_axisMotionController_WHEN_setMillimetersPerSecondIsCalledWithTooSmallValue_THEN_stepperDriverClampedToggleMicrosecondsAreSet
) {
    const uint32_t expectedToggleMicroseconds =
        calculateMicrosecondsBetweenSteps(
            AxisMotionController::MIN_MILLIMETERS_PER_SECOND
        );

    EXPECT_CALL(
        stepperDriverMock_,
        setMicrosecondsBetweenStepToggle(expectedToggleMicroseconds)
    );

    axisMotionController_.setMillimetersPerSecond(
        TOO_SMALL_MILLIMETERS_PER_SECOND
    );
}

TEST_F(
    AxisMotionControllerTest,
    GIVEN_axisMotionController_WHEN_setMillimetersPerSecondIsCalledWithTooBigValue_THEN_errorIsLogged
) {
    axisMotionController_.setMillimetersPerSecond(
        TOO_BIG_MILLIMETERS_PER_SECOND
    );

    EXPECT_THAT(loggerSinkMock_.buffer, HasSubstr("ERROR"));
    EXPECT_THAT(
        loggerSinkMock_.buffer, HasSubstr("Speed [mm/s] out of range:")
    );
}

TEST_F(
    AxisMotionControllerTest,
    GIVEN_axisMotionController_WHEN_setMillimetersPerSecondIsCalledWithTooSmallValue_THEN_errorIsLogged
) {
    axisMotionController_.setMillimetersPerSecond(
        TOO_SMALL_MILLIMETERS_PER_SECOND
    );

    EXPECT_THAT(loggerSinkMock_.buffer, HasSubstr("ERROR"));
    EXPECT_THAT(
        loggerSinkMock_.buffer, HasSubstr("Speed [mm/s] out of range:")
    );
}

TEST_F(
    AxisMotionControllerTest,
    GIVEN_axisMotionController_WHEN_getMillimetersPerSecondIsCalled_THEN_setClampedMillimetersPerSecondIsReturned
) {
    axisMotionController_.setMillimetersPerSecond(
        VALID_MILLIMETERS_PER_SECOND
    );

    ASSERT_EQ(
        axisMotionController_.getMillimetersPerSecond(),
        VALID_MILLIMETERS_PER_SECOND
    );

    axisMotionController_.setMillimetersPerSecond(
        TOO_SMALL_MILLIMETERS_PER_SECOND
    );

    ASSERT_EQ(
        axisMotionController_.getMillimetersPerSecond(),
        AxisMotionController::MIN_MILLIMETERS_PER_SECOND
    );

    axisMotionController_.setMillimetersPerSecond(
        TOO_BIG_MILLIMETERS_PER_SECOND
    );

    ASSERT_EQ(
        axisMotionController_.getMillimetersPerSecond(),
        AxisMotionController::MAX_MILLIMETERS_PER_SECOND
    );
}

TEST_F(
    AxisMotionControllerTest,
    GIVEN_clockwiseForwardAxisMotionController_WHEN_moveToPositionIsCalled_THEN_directionIsSetAndSteppingIsStarted
) {
    constexpr uint32_t forwardPositionInMicrometers = 1000;
    const uint32_t requiredForwardSteps =
        convertMicrometersToSteps(forwardPositionInMicrometers);

    AxisMotionController& clockwiseForwardAxisMotionController =
        axisMotionController_;

    {
        InSequence sequence;

        EXPECT_CALL(stepperDriverMock_, setDirectionClockwise());
        EXPECT_CALL(stepperDriverMock_, startStepping());
        EXPECT_CALL(stepperDriverMock_, stopStepping());
    }

    clockwiseForwardAxisMotionController.moveToPositionInMicrometers(
        forwardPositionInMicrometers
    );

    for (uint32_t i = 0; i < requiredForwardSteps; i++) {
        clockwiseForwardAxisMotionController.handleStepPulseInterrupt();
        clockwiseForwardAxisMotionController.tick();
    }

    ASSERT_TRUE(
        clockwiseForwardAxisMotionController.isAtPositionInMicrometers(
            forwardPositionInMicrometers
        )
    );
    ASSERT_TRUE(clockwiseForwardAxisMotionController.isAtPositionInSteps(
        requiredForwardSteps
    ));

    ASSERT_NEAR(
        clockwiseForwardAxisMotionController
            .getCurrentPositionInMicrometers(),
        forwardPositionInMicrometers,
        POSITION_TOLERANCE_IN_MICROMETERS
    );

    const uint32_t backwardPositionInMicrometers =
        forwardPositionInMicrometers / 2;
    const uint32_t requiredBackwardSteps =
        convertMicrometersToSteps(backwardPositionInMicrometers);

    {
        InSequence sequence;

        EXPECT_CALL(stepperDriverMock_, setDirectionCounterClockwise());
        EXPECT_CALL(stepperDriverMock_, startStepping());
        EXPECT_CALL(stepperDriverMock_, stopStepping());
    }

    clockwiseForwardAxisMotionController.moveToPositionInMicrometers(
        backwardPositionInMicrometers
    );

    for (uint32_t i = 0; i < requiredForwardSteps - requiredBackwardSteps;
         i++) {
        clockwiseForwardAxisMotionController.handleStepPulseInterrupt();
        clockwiseForwardAxisMotionController.tick();
    }

    ASSERT_TRUE(
        clockwiseForwardAxisMotionController.isAtPositionInMicrometers(
            backwardPositionInMicrometers
        )
    );
    ASSERT_TRUE(clockwiseForwardAxisMotionController.isAtPositionInSteps(
        requiredBackwardSteps
    ));

    ASSERT_NEAR(
        clockwiseForwardAxisMotionController
            .getCurrentPositionInMicrometers(),
        backwardPositionInMicrometers,
        POSITION_TOLERANCE_IN_MICROMETERS
    );
}

TEST_F(
    AxisMotionControllerTest,
    GIVEN_counterClockwiseForwardAxisMotionController_WHEN_moveToPositionIsCalled_THEN_directionIsSetAndSteppingIsStarted
) {
    constexpr uint32_t forwardPositionInMicrometers = 1000;
    const uint32_t requiredForwardSteps =
        convertMicrometersToSteps(forwardPositionInMicrometers);

    AxisMotionController counterClockwiseForwardAxisMotionController {
        loggerSinkMock_,
        stepperDriverMock_,
        limitSwitchPair_,
        AXIS_MOTION_PARAMETERS_COUNTERCLOCKWISE_FORWARD
    };

    {
        InSequence sequence;

        EXPECT_CALL(stepperDriverMock_, setDirectionCounterClockwise());
        EXPECT_CALL(stepperDriverMock_, startStepping());
        EXPECT_CALL(stepperDriverMock_, stopStepping());
    }

    counterClockwiseForwardAxisMotionController
        .moveToPositionInMicrometers(forwardPositionInMicrometers);

    for (uint32_t i = 0; i < requiredForwardSteps; i++) {
        counterClockwiseForwardAxisMotionController
            .handleStepPulseInterrupt();
        counterClockwiseForwardAxisMotionController.tick();
    }

    ASSERT_TRUE(
        counterClockwiseForwardAxisMotionController
            .isAtPositionInMicrometers(forwardPositionInMicrometers)
    );
    ASSERT_TRUE(counterClockwiseForwardAxisMotionController
                    .isAtPositionInSteps(requiredForwardSteps));
    ASSERT_NEAR(
        counterClockwiseForwardAxisMotionController
            .getCurrentPositionInMicrometers(),
        forwardPositionInMicrometers,
        POSITION_TOLERANCE_IN_MICROMETERS
    );

    const uint32_t backwardPositionInMicrometers =
        forwardPositionInMicrometers / 2;
    const uint32_t requiredBackwardSteps =
        convertMicrometersToSteps(backwardPositionInMicrometers);

    {
        InSequence sequence;

        EXPECT_CALL(stepperDriverMock_, setDirectionClockwise());
        EXPECT_CALL(stepperDriverMock_, startStepping());
        EXPECT_CALL(stepperDriverMock_, stopStepping());
    }

    counterClockwiseForwardAxisMotionController
        .moveToPositionInMicrometers(backwardPositionInMicrometers);

    for (uint32_t i = 0; i < requiredForwardSteps - requiredBackwardSteps;
         i++) {
        counterClockwiseForwardAxisMotionController
            .handleStepPulseInterrupt();
        counterClockwiseForwardAxisMotionController.tick();
    }

    ASSERT_TRUE(
        counterClockwiseForwardAxisMotionController
            .isAtPositionInMicrometers(backwardPositionInMicrometers)
    );
    ASSERT_TRUE(counterClockwiseForwardAxisMotionController
                    .isAtPositionInSteps(requiredBackwardSteps));

    ASSERT_NEAR(
        counterClockwiseForwardAxisMotionController
            .getCurrentPositionInMicrometers(),
        backwardPositionInMicrometers,
        POSITION_TOLERANCE_IN_MICROMETERS
    );
}

TEST_F(
    AxisMotionControllerTest,
    GIVEN_axisMotionController_WHEN_axisIsAlreadyAtPosition_THEN_stepperDriverDoesNotStartStepping
) {
    constexpr uint32_t position = 100;
    const uint32_t steps = convertMicrometersToSteps(position);

    {
        InSequence sequence {};

        EXPECT_CALL(stepperDriverMock_, startStepping())
            .RetiresOnSaturation();
        EXPECT_CALL(stepperDriverMock_, stopStepping())
            .RetiresOnSaturation();
    }

    axisMotionController_.moveToPositionInMicrometers(position);

    for (uint32_t i = 0; i < steps; i++) {
        axisMotionController_.handleStepPulseInterrupt();
        axisMotionController_.tick();
    }

    ASSERT_TRUE(axisMotionController_.isAtPositionInSteps(steps));

    EXPECT_CALL(stepperDriverMock_, startStepping()).Times(0);
    axisMotionController_.moveToPositionInMicrometers(position);
}

TEST_F(
    AxisMotionControllerTest,
    GIVEN_axisMotionController_WHEN_controllerIsTickedWhenNotMoving_THEN_stepperDriverIsNotInterractedWith
) {
    EXPECT_CALL(stepperDriverMock_, startStepping()).Times(0);
    EXPECT_CALL(stepperDriverMock_, isFaultDetected()).Times(0);

    axisMotionController_.tick();
}

TEST_F(
    AxisMotionControllerTest,
    GIVEN_axisMotionController_WHEN_controllerIsTickedWhenMoving_THEN_stepperDriverFaultIsChecked
) {
    axisMotionController_.moveToPositionInMicrometers(
        VALID_MILLIMETERS_PER_SECOND
    );

    ASSERT_FALSE(axisMotionController_.wasFaultDetected());

    EXPECT_CALL(stepperDriverMock_, isFaultDetected())
        .WillOnce(Return(false))
        .WillOnce(Return(false))
        .WillOnce(Return(true));

    axisMotionController_.tick();
    ASSERT_FALSE(axisMotionController_.wasFaultDetected());

    axisMotionController_.tick();
    ASSERT_FALSE(axisMotionController_.wasFaultDetected());

    axisMotionController_.tick();
    ASSERT_TRUE(axisMotionController_.wasFaultDetected());
}

TEST_F(
    AxisMotionControllerTest,
    GIVEN_axisMotionController_WHEN_minLimitSwitchInterruptOccurs_THEN_stepperDriverIsStopped
) {
    EXPECT_CALL(stepperDriverMock_, stopStepping());

    axisMotionController_.handleMinLimitSwitchInterrupt();
}

TEST_F(
    AxisMotionControllerTest,
    GIVEN_axisMotionController_WHEN_maxLimitSwitchInterruptOccurs_THEN_stepperDriverIsStopped
) {
    EXPECT_CALL(stepperDriverMock_, stopStepping());

    axisMotionController_.handleMaxLimitSwitchInterrupt();
}

TEST_F(
    AxisMotionControllerTest,
    GIVEN_axisMotionController_WHEN_maxLimitSwitchInterruptOccursWhileHoming_THEN_positionIsSetTo0
) {
    constexpr uint32_t position = 30;
    const uint32_t steps = convertMicrometersToSteps(position);

    axisMotionController_.moveToPositionInMicrometers(position);

    for (uint32_t i = 0; i < steps; i++) {
        axisMotionController_.handleStepPulseInterrupt();
        axisMotionController_.tick();
    }

    ASSERT_TRUE(
        axisMotionController_.isAtPositionInMicrometers(position)
    );

    axisMotionController_.homeAxis();
    axisMotionController_.handleMinLimitSwitchInterrupt();

    ASSERT_TRUE(axisMotionController_.isAtPositionInMicrometers(0));
    ASSERT_TRUE(axisMotionController_.isAtPositionInSteps(0));
}

TEST_F(
    AxisMotionControllerTest,
    GIVEN_axisMotionController_WHEN_cancelMovementIsCalled_THEN_stepperDriverStopsStepping
) {
    EXPECT_CALL(stepperDriverMock_, stopStepping());
    axisMotionController_.cancelMovement();
}

TEST_F(
    AxisMotionControllerTest,
    GIVEN_axisMotionController_WHEN_isAtMinLimitCalled_THEN_limitSwitchStateIsReturned
) {
    ON_CALL(minLimitSwitchMock_, isActive()).WillByDefault(Return(false));
    ASSERT_FALSE(axisMotionController_.isAtMinLimit());

    ON_CALL(minLimitSwitchMock_, isActive()).WillByDefault(Return(true));
    ASSERT_TRUE(axisMotionController_.isAtMinLimit());
}

TEST_F(
    AxisMotionControllerTest,
    GIVEN_axisMotionController_WHEN_isAtMaxLimitCalled_THEN_limitSwitchStateIsReturned
) {
    ON_CALL(maxLimitSwitchMock_, isActive()).WillByDefault(Return(false));
    ASSERT_FALSE(axisMotionController_.isAtMaxLimit());

    ON_CALL(maxLimitSwitchMock_, isActive()).WillByDefault(Return(true));
    ASSERT_TRUE(axisMotionController_.isAtMaxLimit());
}
}