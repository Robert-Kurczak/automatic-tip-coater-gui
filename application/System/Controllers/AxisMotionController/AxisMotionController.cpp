#include "AxisMotionController.hpp"

#include "application/System/Config/ComponentConfig/AxisMotionConfig.hpp"
#include "application/System/Controllers/AxisMotionController/AxisMotionParameters.hpp"
#include "application/Utils/Logger.hpp"

#include <algorithm>
#include <cstdint>

namespace ATC {
static constexpr uint16_t MIN_MILLIMETERS_PER_SECOND = 1;
static constexpr uint16_t MAX_MILLIMETERS_PER_SECOND = 1'000;

static constexpr uint32_t MICROSECONDS_IN_SECOND = 1'000'000;
static constexpr uint16_t MICROMETERS_IN_MILLIMETER = 1'000;

static constexpr uint32_t MAX_POSITION_IN_MICROMETERS = 1'000'000;
static constexpr uint32_t MAX_POSITION_IN_STEPS = 2'000'000;

consteval void checkMicrosecondsBetweenStepsOverflows() {
    static_assert(
        (MICROSECONDS_IN_SECOND *
         MAX_AXIS_MOTION_PARAMETERS.millimetersPerRotation) <= UINT32_MAX
    );

    static_assert(
        (MAX_AXIS_MOTION_PARAMETERS.motorStepsPerRotation *
         MAX_AXIS_MOTION_PARAMETERS.driverStepDivider *
         MAX_MILLIMETERS_PER_SECOND) <= UINT32_MAX
    );
}

consteval void checkMicrometersToStepsOverflows() {
    static_assert(
        (MAX_AXIS_MOTION_PARAMETERS.motorStepsPerRotation *
         MAX_AXIS_MOTION_PARAMETERS.driverStepDivider) <= UINT32_MAX
    );

    static_assert(
        (MAX_POSITION_IN_MICROMETERS *
         MAX_AXIS_MOTION_PARAMETERS.motorStepsPerRotation *
         MAX_AXIS_MOTION_PARAMETERS.driverStepDivider /
         MIN_AXIS_MOTION_PARAMETERS.millimetersPerRotation) <= UINT32_MAX
    );
}

consteval void checkStepsToMicrometersOverflows() {
    static_assert(
        (MAX_POSITION_IN_STEPS * MICROMETERS_IN_MILLIMETER *
         MAX_AXIS_MOTION_PARAMETERS.millimetersPerRotation) <= UINT32_MAX
    );
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
    if (micrometers > MAX_POSITION_IN_MICROMETERS) {
        log(loggerSink_,
            LogLevel::Error,
            "Position in micrometers: {} is out of range: <{};{}>"
            "\n\t clamping to: {}",
            micrometers,
            0,
            MAX_POSITION_IN_MICROMETERS,
            MAX_POSITION_IN_MICROMETERS);

        micrometers = MAX_POSITION_IN_MICROMETERS;
    }

    const uint32_t stepsPerMillimeter =
        parameters_.motorStepsPerRotation *
        parameters_.driverStepDivider /
        parameters_.millimetersPerRotation;

    return (micrometers * stepsPerMillimeter) / MICROMETERS_IN_MILLIMETER;
}

[[nodiscard]] uint32_t AxisMotionController::convertStepsToMicrometers(
    uint32_t steps
) const {
    if (steps > MAX_POSITION_IN_STEPS) {
        log(loggerSink_,
            LogLevel::Error,
            "Position in steps: {} is out of range: <{};{}>"
            "\n\t clamping to: {}",
            steps,
            0,
            MAX_POSITION_IN_STEPS,
            MAX_POSITION_IN_STEPS);

        steps = MAX_POSITION_IN_STEPS;
    }

    const uint32_t nominator = steps * MICROMETERS_IN_MILLIMETER *
                               parameters_.millimetersPerRotation;

    const uint32_t denominator =
        parameters_.motorStepsPerRotation * parameters_.driverStepDivider;

    return nominator / denominator;
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
    parameters_(parameters) {
    checkMicrosecondsBetweenStepsOverflows();
    checkMicrometersToStepsOverflows();
    checkStepsToMicrometersOverflows();
}

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