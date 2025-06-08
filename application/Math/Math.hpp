#pragma once

#include <stdint.h>

namespace ATC {
struct Vector2 {
    uint16_t x;
    uint16_t y;
};

struct Rectangle {
    uint16_t xStart;
    uint16_t xEnd;
    uint16_t yStart;
    uint16_t yEnd;
};
}