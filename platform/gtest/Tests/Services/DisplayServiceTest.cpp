#include "application/System/Services/DisplayService/DisplayService.hpp"

#include "application/Utils/Math.hpp"
#include "platform/gtest/Matchers/SpanMatcher.hpp"
#include "platform/gtest/Mocks/Drivers/DisplayMock.hpp"

#include "gtest/gtest.h"
#include <array>

using namespace testing;

namespace ATC {
class DisplayServiceTest : public Test {
public:
    static constexpr std::array<uint16_t, 10>
        FRAMEBUFFER {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    static constexpr Rectangle WINDOW {
        .xStart = 0,
        .xEnd = (FRAMEBUFFER.size() - 1) / 2,
        .yStart = 0,
        .yEnd = (FRAMEBUFFER.size() - 1) / 2
    };

    DisplayMock displayMock_ {};

    DisplayService displayService_ {displayMock_};
};

TEST_F(
    DisplayServiceTest,
    GIVEN_displayService_WHEN_drawIsCalledWithSpecifiedWindow_THEN_callIsForwardedToDisplay
) {
    EXPECT_CALL(displayMock_, draw(SpanValueEq(FRAMEBUFFER), WINDOW));

    displayService_.draw(FRAMEBUFFER, WINDOW);
}

TEST_F(
    DisplayServiceTest,
    GIVEN_displayService_WHEN_drawIsCalled_THEN_callIsForwardedToDisplay
) {
    EXPECT_CALL(displayMock_, draw(SpanValueEq(FRAMEBUFFER)));

    displayService_.draw(FRAMEBUFFER);
}
}