#pragma once

#include <stdint.h>

namespace ATC {
class ISpindleConfiguratorService {
public:
    virtual ~ISpindleConfiguratorService() = default;

    virtual void showcaseRotation() = 0;

    virtual void increaseSpeedPercent() = 0;
    virtual void decreaseSpeedPercent() = 0;
    virtual void saveSpeedPercent() = 0;
    virtual uint8_t getSpeedPercent() const = 0;

    virtual void setDirectionClockwise() = 0;
    virtual void setDirectionCounterClockwise() = 0;
    virtual void saveDirection() = 0;
    virtual bool isDirectionClockwise() const = 0;

    virtual void increaseRotationTimeInMillis() = 0;
    virtual void decreaseRotationTimeInMillis() = 0;
    virtual void saveRotationTimeInMillis() = 0;
    virtual uint32_t getRotationTimeInMillis() const = 0;
};
}