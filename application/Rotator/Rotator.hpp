#pragma once

#include "RotatorTestResults.hpp"
#include "application/Logger/ILogger.hpp"

#include <functional>
#include <stdint.h>

namespace ATC {
using RotatorTestTaskCallback =
    std::function<void(RotatorTestResults results)>;

class Rotator {
private:
    ILogger& logger_;

public:
    Rotator(ILogger& logger);

    void init();
    void tick();

    void startTestTask(RotatorTestTaskCallback callback);

    void increaseSpeed();
    void decreaseSpeed();
    void saveSpeed();
    uint32_t getSpeed();

    void setDirectionClockwise();
    void setDirectionCounterClockwise();
    void saveDirection();
    bool isDirectionClockwise();

    void increaseRotationTime();
    void decreaseRotationTime();
    void saveRotationTime();
    uint32_t getRotationTime();
};
}