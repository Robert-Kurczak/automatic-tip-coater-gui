#pragma once

#include "YAxisTestResults.hpp"

#include <functional>
#include <stdint.h>

namespace ATC {
using YAxisTestTaskCallback =
    std::function<void(YAxisTestResults results)>;

class YAxis {
private:

public:
    void init();
    void tick();

    void startTestTask(YAxisTestTaskCallback callback);

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