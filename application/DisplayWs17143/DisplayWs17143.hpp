#pragma once

#include "application/FlexibleMemoryController/FlexibleMemoryController.hpp"

#include <stdint.h>

class DisplayWs17143 {
private:
    FlexibleMemoryController& flexibleMemoryController;

public:
    DisplayWs17143(FlexibleMemoryController& flexibleMemoryController_);

    void init();
};