#pragma once

#include "application/System/Controllers/AxisController/AxisKinematics/AxisKinematicsParameters.hpp"
#include "application/System/Drivers/LoggerSink/ILoggerSink.hpp"

#include <cstdint>

namespace ATC {
class AxisKinematics {
private:
    ILoggerSink& loggerSink_;
    const AxisKinematicsParameters parameters_;

    const bool areConstParametersInvalid_ = true;

    [[nodiscard]] bool areConstParametersInvalid() const;

    [[nodiscard]] bool areRuntimeParametersInvalid(
        uint16_t millimetersPerSecond
    ) const;

public:
    AxisKinematics(const AxisKinematics&) = delete;
    AxisKinematics& operator=(const AxisKinematics&) = delete;
    AxisKinematics(AxisKinematics&&) = delete;
    AxisKinematics& operator=(AxisKinematics&&) = delete;
    ~AxisKinematics() = delete;

    AxisKinematics(
        ILoggerSink& loggerSink,
        AxisKinematicsParameters parameters
    );

    [[nodiscard]] uint32_t calculateMicrosecondsBetweenSteps(
        uint16_t millimetersPerSecond
    ) const;
};
}