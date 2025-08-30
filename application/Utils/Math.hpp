#pragma once

#include <stdint.h>

namespace ATC {
struct Vector2 {
    uint16_t x_;
    uint16_t y_;
};

struct Rectangle {
    uint16_t xStart_;
    uint16_t xEnd_;
    uint16_t yStart_;
    uint16_t yEnd_;
};
}