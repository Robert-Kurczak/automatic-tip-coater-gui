#pragma once

#include "HeaterTestResults.hpp"

#include <functional>
#include <stdint.h>

namespace ATC {
using HeaterTestTaskCallback =
    std::function<void(HeaterTestResults results)>;

class IHeater {
public:
    virtual void init() = 0;
    virtual void tick() = 0;

    virtual void startTestTask(HeaterTestTaskCallback callback) = 0;

    virtual void setOn() = 0;
    virtual void setOff() = 0;
    virtual void saveState() = 0;
    virtual bool isOn() = 0;

    virtual void increaseTemperature() = 0;
    virtual void decreaseTemperature() = 0;
    virtual void saveTemperature() = 0;
    virtual uint32_t getTemperature() = 0;
};
}