#include "AxisMotionController.hpp"

#include "application/System/Controllers/AxisMotionController/AxisMotionParameters.hpp"
#include "application/Utils/Logger.hpp"

#include <algorithm>
#include <cstdint>

namespace ATC {
static constexpr uint8_t MIN_MILLIMETERS_PER_ROTATION = 1;
static constexpr uint8_t MAX_MILLIMETERS_PER_ROTATION = 50;

static constexpr uint16_t MIN_MOTOR_STEPS_PER_ROTATION = 100;
static constexpr uint16_t MAX_MOTOR_STEPS_PER_ROTATION = 600;

static constexpr uint8_t MIN_DRIVER_STEP_DIVIDER = 1;
static constexpr uint8_t MAX_DRIVER_STEP_DIVIDER = 64;

static constexpr uint16_t MIN_MILLIMETERS_PER_SECOND = 1;
static constexpr uint16_t MAX_MILLIMETERS_PER_SECOND = 3000;

static constexpr uint8_t MIN_STEP_ERROR_MARGIN = 0;
static constexpr uint8_t MAX_STEP_ERROR_MARGIN = 255;

static constexpr uint32_t MICROSECONDS_IN_SECOND = 1'000'000;
static constexpr uint16_t MICROMETERS_IN_MILLIMETER = 1000;

bool AxisMotionController::areParametersWithinRange(
    const AxisMotionParameters& checkedParameters
) const {
    const bool millimetersPerRotationTooSmall =
        checkedParameters.millimetersPerRotation <
        MIN_MILLIMETERS_PER_ROTATION;

    const bool millimetersPerRotationTooBig =
        checkedParameters.millimetersPerRotation >
        MAX_MILLIMETERS_PER_ROTATION;

    const bool motorStepsPerRotationTooSmall =
        checkedParameters.motorStepsPerRotation <
        MIN_MOTOR_STEPS_PER_ROTATION;

    const bool motorStepsPerRotationTooBig =
        checkedParameters.motorStepsPerRotation >
        MAX_MOTOR_STEPS_PER_ROTATION;

    const bool driverStepDividerTooSmall =
        checkedParameters.driverStepDivider < MIN_DRIVER_STEP_DIVIDER;

    const bool driverStepDividerTooBig =
        checkedParameters.driverStepDivider > MAX_DRIVER_STEP_DIVIDER;

    const bool stepErrorMarginTooSmall =
        checkedParameters.stepErrorMargin < MIN_STEP_ERROR_MARGIN;

    const bool stepErrorMarginTooBig =
        checkedParameters.stepErrorMargin > MAX_STEP_ERROR_MARGIN;

    return not millimetersPerRotationTooSmall and
           not millimetersPerRotationTooBig and
           not motorStepsPerRotationTooSmall and
           not motorStepsPerRotationTooBig and
           not driverStepDividerTooSmall and
           not driverStepDividerTooBig and not stepErrorMarginTooSmall and
           not stepErrorMarginTooBig;
}

bool AxisMotionController::isSpeedWithinRange(
    uint16_t millimetersPerSecond
) const {
    const bool millimetersPerSecondTooSmall =
        millimetersPerSecond < MIN_MILLIMETERS_PER_SECOND;

    const bool millimetersPerSecondTooBig =
        millimetersPerSecond > MAX_MILLIMETERS_PER_SECOND;

    return not millimetersPerSecondTooSmall and
           not millimetersPerSecondTooBig;
}

AxisMotionParameters AxisMotionController::clampParameters(
    const AxisMotionParameters& clampedParameters
) const {
    return AxisMotionParameters {
        .millimetersPerRotation = std::clamp(
            clampedParameters.millimetersPerRotation,
            MIN_MILLIMETERS_PER_ROTATION,
            MAX_MILLIMETERS_PER_ROTATION
        ),

        .motorStepsPerRotation = std::clamp(
            clampedParameters.motorStepsPerRotation,
            MIN_MOTOR_STEPS_PER_ROTATION,
            MAX_MOTOR_STEPS_PER_ROTATION
        ),

        .driverStepDivider = std::clamp(
            clampedParameters.driverStepDivider,
            MIN_DRIVER_STEP_DIVIDER,
            MAX_DRIVER_STEP_DIVIDER
        ),

        .isClockwiseRotationForwardMovement =
            clampedParameters.isClockwiseRotationForwardMovement,

        .stepErrorMargin = std::clamp(
            clampedParameters.stepErrorMargin,
            MIN_STEP_ERROR_MARGIN,
            MAX_STEP_ERROR_MARGIN
        )
    };
}

uint32_t AxisMotionController::calculateMicrosecondsBetweenSteps(
    uint16_t millimetersPerSecond
) const {
    if (not isSpeedWithinRange(millimetersPerSecond)) {
        return UINT32_MAX;
    }

    const uint32_t totalStepsPerRotation =
        parameters_.motorStepsPerRotation * parameters_.driverStepDivider;

    return (MICROSECONDS_IN_SECOND * parameters_.millimetersPerRotation) /
           (totalStepsPerRotation * millimetersPerSecond);
}

[[nodiscard]] uint32_t AxisMotionController::convertMicrometersToSteps(
    uint32_t micrometers
) const {
    const uint32_t millimeters = micrometers / MICROMETERS_IN_MILLIMETER;

    const uint32_t stepsPerMillimeter =
        parameters_.motorStepsPerRotation *
        parameters_.driverStepDivider /
        parameters_.millimetersPerRotation;

    return millimeters / stepsPerMillimeter;
}

[[nodiscard]] uint32_t AxisMotionController::convertStepsToMicrometers(
    uint32_t steps
) const {
    const uint32_t nominator = steps * MICROMETERS_IN_MILLIMETER *
                               parameters_.millimetersPerRotation;

    const uint32_t denominator =
        parameters_.motorStepsPerRotation * parameters_.driverStepDivider;

    return nominator / denominator;
}

void AxisMotionController::logParametersClampStatus() {
    if (wereParametersClamped_) {
        log(loggerSink_,
            LogLevel::Error,
            "Axis motion parameters were out of range."
            "Clamped them to values:"
            "\n\t millimeters per rotation: {} | range: <{}, {}>"
            "\n\t motor steps per rotation: {} | range: <{}, {}>"
            "\n\t driver step divider: {} | range: <{}, {}>"
            "\n\t step error margin: {} | range: <{}, {}>",

            parameters_.millimetersPerRotation,
            MIN_MILLIMETERS_PER_ROTATION,
            MAX_MILLIMETERS_PER_ROTATION,

            parameters_.motorStepsPerRotation,
            MIN_MOTOR_STEPS_PER_ROTATION,
            MAX_MOTOR_STEPS_PER_ROTATION,

            parameters_.driverStepDivider,
            MIN_DRIVER_STEP_DIVIDER,
            MAX_DRIVER_STEP_DIVIDER,

            parameters_.stepErrorMargin,
            MIN_STEP_ERROR_MARGIN,
            MAX_STEP_ERROR_MARGIN);
    }
}

void AxisMotionController::checkDriverFault() {
    if (not wasFaultDetected_ and stepperDriver_.isFaultDetected()) {
        wasFaultDetected_ = true;
    }
}

void AxisMotionController::setDirection(bool moveForward) {
    isDirectionForward_ = moveForward;

    const bool rotateClockwise =
        moveForward == parameters_.isClockwiseRotationForwardMovement;

    if (rotateClockwise) {
        stepperDriver_.setDirectionClockwise();
    } else {
        stepperDriver_.setDirectionCounterClockwise();
    }
}

void AxisMotionController::setDirectionForward() {
    setDirection(true);
}

void AxisMotionController::setDirectionBackward() {
    setDirection(false);
}

AxisMotionController::AxisMotionController(
    ILoggerSink& loggerSink,
    IStepperDriver& stepperDriver,
    LimitSwitchPair& limitSwitchPair,
    AxisMotionParameters parameters
) :
    loggerSink_(loggerSink),
    stepperDriver_(stepperDriver),
    limitSwitchPair_(limitSwitchPair),
    wereParametersClamped_(not areParametersWithinRange(parameters)),
    parameters_(clampParameters(parameters)) {}

void AxisMotionController::init() {
    stepperDriver_.init();
    stepperDriver_.stopStepping();
}

void AxisMotionController::tick() {
    if (not isMovingToTarget_) {
        return;
    }

    if (isAtPositionInSteps(targetPositionInSteps_)) {
        isMovingToTarget_ = false;
        stepperDriver_.stopStepping();
    }

    checkDriverFault();
}

void AxisMotionController::handleStepPulseInterrupt() {
    if (isMovingToTarget_) {
        currentPositionInSteps_ += isDirectionForward_ ? +1 : -1;
    }
}

void AxisMotionController::handleMinLimitSwitchInterrupt() {
    stepperDriver_.stopStepping();

    if (isHoming_) {
        currentPositionInSteps_ = 0;
        isHoming_ = false;
    }
}

void AxisMotionController::handleMaxLimitSwitchInterrupt() {
    stepperDriver_.stopStepping();
}

[[nodiscard]] bool AxisMotionController::wasFaultDetected() const {
    return wasFaultDetected_;
}

void AxisMotionController::setMillimetersPerSecond(uint16_t value) {
    if (not isSpeedWithinRange(value)) {
        log(loggerSink_,
            LogLevel::Error,
            "Speed [mm/s] out of range:"
            "\n\t value: {} | range: <{}, {}>"
            "\n\t Clamping to nearest",
            value,
            MIN_MILLIMETERS_PER_SECOND,
            MAX_MILLIMETERS_PER_SECOND);

        value = std::clamp(
            value, MIN_MILLIMETERS_PER_SECOND, MAX_MILLIMETERS_PER_SECOND
        );
    }

    currentMillimetersPerSecond_ = value;

    const uint32_t toggleMicroseconds =
        calculateMicrosecondsBetweenSteps(value);

    stepperDriver_.setMicrosecondsBetweenStepToggle(toggleMicroseconds);
}

uint16_t AxisMotionController::getMillimetersPerSecond() const {
    return currentMillimetersPerSecond_;
}

void AxisMotionController::moveToPositionInMicrometers(uint32_t value) {
    targetPositionInSteps_ = convertMicrometersToSteps(value);
    isMovingToTarget_ = true;

    if (targetPositionInSteps_ > currentPositionInSteps_) {
        setDirectionForward();
    } else {
        setDirectionBackward();
    }

    stepperDriver_.startStepping();
}

void AxisMotionController::moveToMinLimitSwitch() {
    setDirectionBackward();
    stepperDriver_.startStepping();
}

void AxisMotionController::moveToMaxLimitSwitch() {
    setDirectionForward();
    stepperDriver_.startStepping();
}

void AxisMotionController::homeAxis() {
    isHoming_ = true;
    moveToMinLimitSwitch();
}

bool AxisMotionController::isAtPositionInMicrometers(
    uint32_t value
) const {
    const uint32_t steps = convertMicrometersToSteps(value);
    return isAtPositionInSteps(steps);
}

[[nodiscard]] bool AxisMotionController::isAtPositionInSteps(
    uint32_t value
) const {
    const uint32_t absoluteDifference =
        value > currentPositionInSteps_ ? value - currentPositionInSteps_
                                        : currentPositionInSteps_ - value;

    return absoluteDifference <= parameters_.stepErrorMargin;
}

uint32_t AxisMotionController::getCurrentPositionInMicrometers() const {
    return convertStepsToMicrometers(currentPositionInSteps_);
}

bool AxisMotionController::isAtMinLimit() const {
    return limitSwitchPair_.minLimitSwitch.isActive();
}

bool AxisMotionController::isAtMaxLimit() const {
    return limitSwitchPair_.maxLimitSwitch.isActive();
}

void AxisMotionController::cancelMovement() {
    isMovingToTarget_ = false;
    isHoming_ = false;
    stepperDriver_.stopStepping();
}
}