#pragma once

#include <stdint.h>

namespace ATC {
class YAxis {
private:

public:
    void increaseStartPosition();
    void decreaseStartPosition();
    void saveStartPosition();
    uint32_t getStartPosition();

    void increaseEndPosition();
    void decreaseEndPosition();
    void saveEndPosition();
    uint32_t getEndPosition();

    void increaseSpeed();
    void decreaseSpeed();
    void saveSpeed();
    uint32_t getSpeed();
};
}