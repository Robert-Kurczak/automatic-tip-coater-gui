#pragma once

#include <cstdint>

namespace ATC {
class IMotorDriver {
public:
    IMotorDriver() = default;
    IMotorDriver(const IMotorDriver&) = delete;
    IMotorDriver& operator=(const IMotorDriver&) = delete;
    IMotorDriver(IMotorDriver&&) = delete;
    IMotorDriver& operator=(IMotorDriver&&) = delete;
    virtual ~IMotorDriver() = default;

    virtual void init() = 0;

    virtual void startRotation(uint8_t speedPercent) = 0;
    virtual void stopRotation() = 0;

    virtual void setDirectionClockwise() = 0;
    virtual void setDirectionCounterClockwise() = 0;
    [[nodiscard]] virtual bool isDirectionClockwise() const = 0;

    [[nodiscard]] virtual bool isFaultDetected() = 0;
};
}