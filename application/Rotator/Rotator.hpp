#pragma once
#include <stdint.h>

namespace ATC {
class Rotator {
private:

public:
    void init();

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