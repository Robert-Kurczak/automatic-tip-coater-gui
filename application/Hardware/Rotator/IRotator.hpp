#pragma once

#include "RotatorTestResults.hpp"

#include <functional>
#include <stdint.h>

namespace ATC {
using RotatorTestTaskCallback =
    std::function<void(RotatorTestResults results)>;

class IRotator {
public:
    virtual void tick() = 0;
    virtual void init() = 0;

    virtual void startTestTask(RotatorTestTaskCallback callback) = 0;

    virtual void increaseSpeed() = 0;
    virtual void decreaseSpeed() = 0;
    virtual void saveSpeed() = 0;
    virtual uint32_t getSpeed() = 0;

    virtual void setDirectionClockwise() = 0;
    virtual void setDirectionCounterClockwise() = 0;
    virtual void saveDirection() = 0;
    virtual bool isDirectionClockwise() = 0;

    virtual void increaseRotationTime() = 0;
    virtual void decreaseRotationTime() = 0;
    virtual void saveRotationTime() = 0;
    virtual uint32_t getRotationTime() = 0;
};
}