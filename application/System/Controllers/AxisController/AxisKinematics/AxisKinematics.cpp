#include "AxisKinematics.hpp"

#include "application/Utils/Logger.hpp"

#include <cstdint>

namespace ATC {
static constexpr uint16_t MIN_MOTOR_STEPS_PER_ROTATION = 1;
static constexpr uint16_t MAX_MOTOR_STEPS_PER_ROTATION = 5000;

static constexpr uint16_t MIN_DRIVER_STEP_DIVIDER = 1;
static constexpr uint16_t MAX_DRIVER_STEP_DIVIDER = 256;

static constexpr uint16_t MIN_MILLIMETERS_PER_SECOND = 1;
static constexpr uint16_t MAX_MILLIMETERS_PER_SECOND = 3000;

bool AxisKinematics::areConstParametersInvalid() const {
    const bool motorStepsPerRotationTooSmall =
        parameters_.motorStepsPerRotation < MIN_MOTOR_STEPS_PER_ROTATION;

    const bool motorStepsPerRotationTooBig =
        parameters_.motorStepsPerRotation > MAX_MOTOR_STEPS_PER_ROTATION;

    const bool driverStepDividerTooSmall =
        parameters_.driverStepDivider < MIN_DRIVER_STEP_DIVIDER;

    const bool driverStepDividerTooBig =
        parameters_.driverStepDivider > MAX_DRIVER_STEP_DIVIDER;

    return motorStepsPerRotationTooSmall || motorStepsPerRotationTooBig ||
           driverStepDividerTooSmall || driverStepDividerTooBig;
}

bool AxisKinematics::areRuntimeParametersInvalid(
    uint16_t millimetersPerSecond
) const {
    const bool millimetersPerSecondTooSmall =
        millimetersPerSecond < MIN_MILLIMETERS_PER_SECOND;

    const bool millimetersPerSecondTooBig =
        millimetersPerSecond > MAX_MILLIMETERS_PER_SECOND;

    return millimetersPerSecondTooSmall || millimetersPerSecondTooBig;
}

AxisKinematics::AxisKinematics(
    ILoggerSink& loggerSink,
    AxisKinematicsParameters parameters
) :
    loggerSink_(loggerSink),
    parameters_(parameters),
    areConstParametersInvalid_ {areConstParametersInvalid()} {}

uint32_t AxisKinematics::calculateMicrosecondsBetweenSteps(
    uint16_t millimetersPerSecond
) const {
    if (areConstParametersInvalid_ ||
        areRuntimeParametersInvalid(millimetersPerSecond)) {
        log(loggerSink_,
            LogLevel::Error,
            "Axis kinematics parameters are out of range:"
            "\n\t motor steps per rotation: {} | range: <{}, {}>",
            "\n\t driver steps divider: {} | range: <{}, {}>",
            "\n\t millimetersPerSecond: {} | range: <{}, {}>",

            parameters_.motorStepsPerRotation,
            MIN_MOTOR_STEPS_PER_ROTATION,
            MAX_MOTOR_STEPS_PER_ROTATION,

            parameters_.driverStepDivider,
            MIN_DRIVER_STEP_DIVIDER,
            MAX_DRIVER_STEP_DIVIDER,

            millimetersPerSecond,
            MIN_MILLIMETERS_PER_SECOND,
            MAX_MILLIMETERS_PER_SECOND);

        return UINT32_MAX;
    }

    const uint32_t microsecondsInSecond = 1'000'000;

    const uint32_t totalStepsPerRotation =
        parameters_.motorStepsPerRotation * parameters_.driverStepDivider;

    return (microsecondsInSecond * parameters_.millimetersPerRotation) /
           (totalStepsPerRotation * millimetersPerSecond);
}
}