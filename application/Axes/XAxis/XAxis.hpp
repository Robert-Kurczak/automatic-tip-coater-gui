#pragma once

#include "XAxisTestResults.hpp"

#include <functional>
#include <stdint.h>

namespace ATC {
using XAxisTestTaskCallback =
    std::function<void(XAxisTestResults results)>;

class XAxis {
private:

public:
    void init();
    void tick();

    void startTestTask(XAxisTestTaskCallback callback);

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