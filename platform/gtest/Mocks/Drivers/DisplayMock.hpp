#pragma once

#include "application/System/Drivers/Display/IDisplay.hpp"

#include "gmock/gmock.h"

namespace ATC {
class DisplayMock : public IDisplay {
public:
    MOCK_METHOD(void, init, (), (override));

    MOCK_METHOD(void, drawTestPattern, (uint8_t seed), (override));

    MOCK_METHOD(
        void,
        draw,
        (const std::span<const uint16_t>& framebuffer,
         const Rectangle& window),
        (override)
    );

    MOCK_METHOD(
        void,
        draw,
        (const std::span<const uint16_t>& framebuffer),
        (override)
    );
};
}