#pragma once

#include <stdint.h>

namespace ATC {
class IMotor {
public:
    virtual ~IMotor() = default;

    virtual void init() = 0;

    virtual void startRotation(uint8_t speedPercent) = 0;
    virtual void stopRotation() = 0;

    virtual void setDirectionClockwise() = 0;
    virtual void setDirectionCounterClockwise() = 0;
    virtual bool isDirectionClockwise() const = 0;
};
}