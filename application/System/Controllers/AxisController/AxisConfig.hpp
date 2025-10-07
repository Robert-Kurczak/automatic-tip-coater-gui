#pragma once

#include <stdint.h>

namespace ATC {
struct AxisConfig {
    uint32_t startPosition;
    uint32_t endPosition;
    uint32_t speed;
};
}