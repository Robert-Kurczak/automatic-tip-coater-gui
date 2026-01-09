#pragma once

#include <cstdint>

namespace ATC {
class IMotor {
public:
    IMotor() = default;
    IMotor(const IMotor&) = delete;
    IMotor& operator=(const IMotor&) = delete;
    IMotor(IMotor&&) = delete;
    IMotor& operator=(IMotor&&) = delete;
    virtual ~IMotor() = default;

    virtual void init() = 0;

    virtual void startRotation(uint8_t speedPercent) = 0;
    virtual void stopRotation() = 0;

    virtual void setDirectionClockwise() = 0;
    virtual void setDirectionCounterClockwise() = 0;
    [[nodiscard]] virtual bool isDirectionClockwise() const = 0;

    [[nodiscard]] virtual bool isFaultDetected() = 0;
};
}