#pragma once

#include <stdint.h>

namespace ATC {
class Heater {
private:

public:
    void init();

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