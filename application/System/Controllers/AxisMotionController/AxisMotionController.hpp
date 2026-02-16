#pragma once

#include "AxisMotionParameters.hpp"
#include "IAxisMotionController.hpp"
#include "application/System/Drivers/LimitSwitch/ILimitSwitch.hpp"
#include "application/System/Drivers/LoggerSink/ILoggerSink.hpp"
#include "application/System/Drivers/StepperDriver/IStepperDriver.hpp"

#include <cstdint>

namespace ATC {
struct LimitSwitchPair {
    // NOLINTBEGIN(cppcoreguidelines-avoid-const-or-ref-data-members)
    ILimitSwitch& minLimitSwitch;
    ILimitSwitch& maxLimitSwitch;
    // NOLINTEND(cppcoreguidelines-avoid-const-or-ref-data-members)
};

class AxisMotionController : public IAxisMotionController {
private:
    ILoggerSink& loggerSink_;
    IStepperDriver& stepperDriver_;
    LimitSwitchPair& limitSwitchPair_;

    const AxisMotionParameters parameters_;

    bool wasFaultDetected_ = false;
    bool isDirectionForward_ = true;
    volatile bool isMovingToTarget_ = false;
    volatile bool isHoming_ = false;

    uint16_t currentMillimetersPerSecond_ = 0;
    volatile uint32_t currentPositionInSteps_ = 0;
    uint32_t targetPositionInSteps_ = 0;

    [[nodiscard]] bool isSpeedWithinRange(
        uint16_t millimetersPerSecond
    ) const;

    [[nodiscard]] uint32_t calculateStepsToTargetPosition() const;

    [[nodiscard]] uint32_t calculateMicrosecondsBetweenSteps(
        uint16_t millimetersPerSecond
    ) const;

    [[nodiscard]] uint32_t convertMicrometersToSteps(
        uint32_t micrometers
    ) const;

    [[nodiscard]] uint32_t convertStepsToMicrometers(
        uint32_t steps
    ) const;

    void logParametersClampStatus();
    void checkDriverFault();

    void setDirection(bool moveForward);
    void setDirectionForward();
    void setDirectionBackward();

public:
    static constexpr uint16_t MIN_MILLIMETERS_PER_SECOND = 1;
    static constexpr uint16_t MAX_MILLIMETERS_PER_SECOND = 1'000;

    AxisMotionController(
        ILoggerSink& loggerSink,
        IStepperDriver& stepperDriver,
        LimitSwitchPair& limitSwitchPair,
        AxisMotionParameters parameters
    );

    void init() override;
    void tick() override;

    void handleStepPulseInterrupt() override;
    void handleMinLimitSwitchInterrupt() override;
    void handleMaxLimitSwitchInterrupt() override;

    [[nodiscard]] bool wasFaultDetected() const override;

    void setMillimetersPerSecond(uint16_t value) override;
    [[nodiscard]] uint16_t getMillimetersPerSecond() const override;

    void moveToPositionInMicrometers(uint32_t value) override;
    void moveToMinLimitSwitch() override;
    void moveToMaxLimitSwitch() override;
    void homeAxis() override;

    [[nodiscard]] bool isAtPositionInMicrometers(
        uint32_t value
    ) const override;

    [[nodiscard]] bool isAtPositionInSteps(uint32_t value) const override;

    [[nodiscard]] uint32_t
    getCurrentPositionInMicrometers() const override;

    [[nodiscard]] bool isAtMinLimit() const override;
    [[nodiscard]] bool isAtMaxLimit() const override;

    void cancelMovement() override;
};
}