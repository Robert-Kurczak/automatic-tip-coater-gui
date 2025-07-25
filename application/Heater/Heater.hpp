#pragma once

#include "HeaterTestResults.hpp"

#include <functional>
#include <stdint.h>

namespace ATC {
using HeaterTestTaskCallback =
    std::function<void(HeaterTestResults results)>;

class Heater {
private:

public:
    void init();
    void tick();

    void startTestTask(HeaterTestTaskCallback callback);

    void setOn();
    void setOff();
    void saveState();
    bool isOn();

    void increaseTemperature();
    void decreaseTemperature();
    void saveTemperature();
    uint32_t getTemperature();
};
}