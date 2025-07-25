#pragma once

#include "ZAxisTestResults.hpp"

#include <functional>
#include <stdint.h>

namespace ATC {
using ZAxisTestTaskCallback =
    std::function<void(ZAxisTestResults results)>;

class ZAxis {
private:

public:
    void init();
    void tick();

    void startTestTask(ZAxisTestTaskCallback callback);

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