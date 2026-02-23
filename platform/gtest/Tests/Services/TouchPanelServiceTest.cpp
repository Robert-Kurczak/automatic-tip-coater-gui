#include "application/System/Services/TouchPanelService/TouchPanelService.hpp"

#include "application/Utils/Math.hpp"
#include "platform/gtest/Mocks/Controllers/TouchPanelControllerMock.hpp"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

using namespace testing;

namespace ATC {
class TouchPanelServiceTest : public Test {
public:
    TouchPanelControllerMock touchPanelControllerMock_ {};

    TouchPanelService touchPanelService_ {touchPanelControllerMock_};
};

TEST_F(
    TouchPanelServiceTest,
    GIVEN_touchPanelService_WHEN_readPositionIsCalled_THEN_callIsForwardedToController
) {
    constexpr Vector2 position {.x = 50, .y = 25};

    EXPECT_CALL(touchPanelControllerMock_, readPosition())
        .WillOnce(Return(position));

    EXPECT_EQ(touchPanelService_.readPosition(), position);
}
}