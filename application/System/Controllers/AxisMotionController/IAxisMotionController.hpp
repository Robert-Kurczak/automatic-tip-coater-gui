#pragma once

#include <cstdint>

namespace ATC {
class IAxisMotionController {
public:
    IAxisMotionController() = default;
    IAxisMotionController(const IAxisMotionController&) = delete;
    IAxisMotionController& operator=(const IAxisMotionController&) =
        delete;
    IAxisMotionController(IAxisMotionController&&) = delete;
    IAxisMotionController& operator=(IAxisMotionController&&) = delete;

    virtual ~IAxisMotionController() = default;

    virtual void init() = 0;
    virtual void tick() = 0;

    virtual void handleStepPulseInterrupt() = 0;
    virtual void handleMinLimitSwitchInterrupt() = 0;
    virtual void handleMaxLimitSwitchInterrupt() = 0;

    [[nodiscard]] virtual bool wasFaultDetected() const = 0;

    virtual void setMillimetersPerSecond(uint16_t value) = 0;
    [[nodiscard]] virtual uint16_t getMillimetersPerSecond() const = 0;

    virtual void moveTo(uint32_t position) = 0;
    virtual void moveToMinLimitSwitch() = 0;
    virtual void moveToMaxLimitSwitch() = 0;
    virtual void homeAxis() = 0;

    [[nodiscard]] virtual bool isAtPosition(uint32_t position) const = 0;
    [[nodiscard]] virtual uint32_t getCurrentPosition() const = 0;

    [[nodiscard]] virtual bool isAtMinLimit() const = 0;
    [[nodiscard]] virtual bool isAtMaxLimit() const = 0;

    virtual void cancelMovement() = 0;
};
}