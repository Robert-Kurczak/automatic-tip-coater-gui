#pragma once

#include <cstdint>

namespace ATC {
struct Vector2 {
    uint16_t x;
    uint16_t y;

    constexpr bool operator==(const Vector2&) const = default;
};

struct Rectangle {
    uint16_t xStart;
    uint16_t xEnd;
    uint16_t yStart;
    uint16_t yEnd;

    constexpr bool operator==(const Rectangle&) const = default;
};
}