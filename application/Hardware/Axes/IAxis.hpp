#pragma once

#include "AxisTestResults.hpp"

#include <stdint.h>
#include <functional>

namespace ATC {
using AxisTestTaskCallback = std::function<void(AxisTestResults results)>;

class IAxis {
public:
    virtual void init() = 0;
    virtual void tick() = 0;

    virtual void startTestTask(AxisTestTaskCallback callback) = 0;

    virtual void increaseStartPosition() = 0;
    virtual void decreaseStartPosition() = 0;
    virtual void saveStartPosition() = 0;
    virtual uint32_t getStartPosition() = 0;

    virtual void increaseEndPosition() = 0;
    virtual void decreaseEndPosition() = 0;
    virtual void saveEndPosition() = 0;
    virtual uint32_t getEndPosition() = 0;

    virtual void increaseSpeed() = 0;
    virtual void decreaseSpeed() = 0;
    virtual void saveSpeed() = 0;
    virtual uint32_t getSpeed() = 0;

    virtual ~IAxis() {};
};
}
