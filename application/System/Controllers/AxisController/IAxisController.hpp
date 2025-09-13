#pragma once

#include <stdint.h>

namespace ATC {
class IAxisController {
public:
    virtual ~IAxisController() = default;

    virtual void init() = 0;
    virtual void tick() = 0;

    virtual bool wasFaultReported() const = 0;

    virtual void moveToMinLimitPosition() = 0;
    virtual bool isAtMinLimitPosition() const = 0;

    virtual void moveToMaxLimitPosition() = 0;
    virtual bool isAtMaxLimitPosition() const = 0;

    virtual void moveToHomePosition() = 0;
    virtual bool isAtHomePosition() const = 0;

    virtual void moveToStartPosition() = 0;
    virtual bool isAtStartPosition() const = 0;

    virtual void moveToEndPosition() = 0;
    virtual bool isAtEndPosition() const = 0;

    virtual void setStartPosition(uint32_t value) = 0;
    virtual uint32_t getStartPosition() const = 0;

    virtual void setEndPosition(uint32_t value) = 0;
    virtual uint32_t getEndPosition() const = 0;

    virtual void setSpeed(uint32_t value) = 0;
    virtual uint32_t getSpeed() const = 0;
};
}