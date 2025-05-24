#pragma once

#include "application/FlexibleMemoryController/FlexibleMemoryController.hpp"

#include <stdint.h>

class DisplayWs17143 {
private:
    FlexibleMemoryController& flexibleMemoryController;

public:
    DisplayWs17143(FlexibleMemoryController& flexibleMemoryController_);

    void init();
    void setWindow(
        const uint16_t startX,
        const uint16_t endX,
        const uint16_t startY,
        const uint16_t endY
    );
};