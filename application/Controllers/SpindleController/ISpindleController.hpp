#pragma once

#include <stdint.h>

namespace ATC {
class ISpindleController {
public:
    virtual void tick() = 0;
    virtual void init() = 0;

    virtual void startRotation() = 0;

    virtual void startTimedRotation(uint32_t rotationMillis) = 0;
    virtual void startTimedRotation() = 0;

    virtual void stopRotation() = 0;

    virtual bool isTimedRotationFinished() const = 0;

    virtual void setDirectionClockwise() = 0;
    virtual void setDirectionCounterClockwise() = 0;
    virtual bool isDirectionClockwise() const = 0;

    virtual void setSpeedPercent(uint8_t value) = 0;
    virtual uint8_t getSpeedPercent() const = 0;

    virtual void setRotationTimeMillis(uint32_t value) = 0;
    virtual uint32_t getRotationTimeMillis() const = 0;
};
}