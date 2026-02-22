#include "application/System/Controllers/TouchPanelController/ResistiveTouchPanelController/ResistiveTouchPanelController.hpp"

#include "application/System/Controllers/TouchPanelController/ResistiveTouchPanelController/ResistiveTouchPanelParameters.hpp"
#include "application/Utils/Math.hpp"
#include "platform/gtest/Mocks/Drivers/ResistiveTouchPanelMock.hpp"
#include "platform/gtest/Mocks/Ports/SystemClockMock.hpp"

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <cstdint>
#include <format>
#include <iostream>

using namespace testing;

namespace ATC {
class ResistiveTouchPanelControllerTest : public Test {
public:
    static constexpr ResistiveTouchPanelParameters PARAMETERS {
        .rawWorkingArea =
            Rectangle {
                       .xStart = 20,
                       .xEnd = 1900,
                       .yStart = 10,
                       .yEnd = 1800
            },

        .pixelResolution = Vector2 {.x = 500, .y = 1000},
        .pressureTreshold = 1000,
        .invertYAxis = false
    };

    static constexpr Vector2 VALID_RAW_POSITION {
        .x = uint16_t(
                 0.62 * (PARAMETERS.rawWorkingArea.xEnd -
                         PARAMETERS.rawWorkingArea.xStart)
             ) +
             PARAMETERS.rawWorkingArea.xStart,
        .y = uint16_t(
                 0.38 * (PARAMETERS.rawWorkingArea.yEnd -
                         PARAMETERS.rawWorkingArea.yStart)
             ) +
             PARAMETERS.rawWorkingArea.yStart
    };

    static constexpr Vector2 VALID_INTERPOLATED_POSITION {
        .x = uint16_t(0.62 * PARAMETERS.pixelResolution.x),
        .y = uint16_t(0.38 * PARAMETERS.pixelResolution.y)
    };

    static constexpr uint32_t SUFFICIENT_TOUCH_PRESSURE =
        PARAMETERS.pressureTreshold - 1;

    static constexpr uint32_t INSUFFICIENT_TOUCH_PRESSURE =
        PARAMETERS.pressureTreshold + 1;

    static constexpr Vector2 MAX_POSITION_VALUE {
        .x = UINT16_MAX,
        .y = UINT16_MAX
    };

    ResistiveTouchPanelMock resistiveTouchPanelMock_ {};
    SystemClockMock systemClockMock_ {};

    ResistiveTouchPanelController resistiveTouchPanelController_ {
        resistiveTouchPanelMock_,
        systemClockMock_,
        PARAMETERS
    };

    void expectValidTouch(uint32_t pressure) {
        EXPECT_CALL(resistiveTouchPanelMock_, isTouchDetected())
            .WillRepeatedly(Return(true));

        EXPECT_CALL(resistiveTouchPanelMock_, readRawZ())
            .WillRepeatedly(Return(pressure));

        EXPECT_CALL(systemClockMock_, getMillisecondsSinceStart())
            .WillRepeatedly([]() {
                constexpr uint32_t millisecondsBetweenCalls = 20;
                static uint32_t callAmount = 0;
                callAmount++;
                return callAmount * millisecondsBetweenCalls;
            });
    }
};

TEST_F(
    ResistiveTouchPanelControllerTest,
    GIVEN_resistiveTouchPanelController_WHEN_controllerIsInitialized_THEN_resistiveTouchPanelIsSetUp
) {
    EXPECT_CALL(resistiveTouchPanelMock_, init());

    resistiveTouchPanelController_.init();
}

TEST_F(
    ResistiveTouchPanelControllerTest,
    GIVEN_resistiveTouchPanelController_WHEN_touchIsNotDetected_THEN_maxPositionIsReturned
) {
    EXPECT_CALL(resistiveTouchPanelMock_, isTouchDetected())
        .WillOnce(Return(false));

    ASSERT_EQ(
        resistiveTouchPanelController_.readPosition(), MAX_POSITION_VALUE
    );
}

TEST_F(
    ResistiveTouchPanelControllerTest,
    GIVEN_resistiveTouchPanelController_WHEN_sufficientTouchPressureIsDetected_THEN_validPositionIsReturned
) {
    expectValidTouch(SUFFICIENT_TOUCH_PRESSURE);

    EXPECT_CALL(resistiveTouchPanelMock_, readRawX())
        .WillRepeatedly(Return(VALID_RAW_POSITION.x));

    EXPECT_CALL(resistiveTouchPanelMock_, readRawY())
        .WillRepeatedly(Return(VALID_RAW_POSITION.y));

    const Vector2 readPosition =
        resistiveTouchPanelController_.readPosition();

    std::cout << std::format(
        "Read position: x: {}, y: {}\n", readPosition.x, readPosition.y
    );
    std::cout << std::format(
        "Expected position: x: {}, y: {}\n",
        VALID_INTERPOLATED_POSITION.x,
        VALID_INTERPOLATED_POSITION.y
    );

    ASSERT_NEAR(readPosition.x, VALID_INTERPOLATED_POSITION.x, 3);
    ASSERT_NEAR(readPosition.y, VALID_INTERPOLATED_POSITION.y, 3);
}

TEST_F(
    ResistiveTouchPanelControllerTest,
    GIVEN_resistiveTouchPanelController_WHEN_insufficientTouchPressureIsDetected_THEN_maxPositionIsReturned
) {
    expectValidTouch(INSUFFICIENT_TOUCH_PRESSURE);

    EXPECT_CALL(resistiveTouchPanelMock_, readRawX())
        .WillRepeatedly(Return(VALID_RAW_POSITION.x));

    EXPECT_CALL(resistiveTouchPanelMock_, readRawY())
        .WillRepeatedly(Return(VALID_RAW_POSITION.y));

    EXPECT_EQ(
        resistiveTouchPanelController_.readPosition(), MAX_POSITION_VALUE
    );
}

TEST_F(
    ResistiveTouchPanelControllerTest,
    GIVEN_resistiveTouchPanelController_WHEN_touchSignalIsTooShort_THEN_maxValueIsReturned
) {
    EXPECT_CALL(resistiveTouchPanelMock_, isTouchDetected())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(resistiveTouchPanelMock_, readRawZ())
        .WillRepeatedly(Return(SUFFICIENT_TOUCH_PRESSURE));

    constexpr uint32_t signalMilliseconds = 15;

    {
        InSequence sequence;

        EXPECT_CALL(systemClockMock_, getMillisecondsSinceStart())
            .WillRepeatedly(Return(0));

        EXPECT_CALL(systemClockMock_, getMillisecondsSinceStart())
            .WillRepeatedly(Return(signalMilliseconds));
    }

    ASSERT_EQ(
        resistiveTouchPanelController_.readPosition(), MAX_POSITION_VALUE
    );
}

TEST_F(
    ResistiveTouchPanelControllerTest,
    GIVEN_resistiveTouchPanelController_WHEN_touchSignalIsBouncing_THEN_signalIsDebounced
) {
    EXPECT_CALL(resistiveTouchPanelMock_, isTouchDetected())
        .WillRepeatedly(Return(true));

    constexpr uint32_t timestamp1 = 0;
    constexpr uint32_t timestamp2 = 10;
    constexpr uint32_t timestamp3 = 15;
    constexpr uint32_t timestamp4 = 100;

    EXPECT_CALL(systemClockMock_, getMillisecondsSinceStart())
        .WillRepeatedly(Return(timestamp1));

    EXPECT_CALL(resistiveTouchPanelMock_, readRawZ())
        .WillRepeatedly(Return(SUFFICIENT_TOUCH_PRESSURE));

    ASSERT_EQ(
        resistiveTouchPanelController_.readPosition(), MAX_POSITION_VALUE
    );

    EXPECT_CALL(systemClockMock_, getMillisecondsSinceStart())
        .WillRepeatedly(Return(timestamp2));

    EXPECT_CALL(resistiveTouchPanelMock_, readRawZ())
        .WillRepeatedly(Return(INSUFFICIENT_TOUCH_PRESSURE));

    ASSERT_EQ(
        resistiveTouchPanelController_.readPosition(), MAX_POSITION_VALUE
    );

    EXPECT_CALL(systemClockMock_, getMillisecondsSinceStart())
        .WillRepeatedly(Return(timestamp3));

    EXPECT_CALL(resistiveTouchPanelMock_, readRawZ())
        .WillRepeatedly(Return(SUFFICIENT_TOUCH_PRESSURE));

    ASSERT_EQ(
        resistiveTouchPanelController_.readPosition(), MAX_POSITION_VALUE
    );

    EXPECT_CALL(systemClockMock_, getMillisecondsSinceStart())
        .WillRepeatedly(Return(timestamp4));

    ASSERT_NE(
        resistiveTouchPanelController_.readPosition(), MAX_POSITION_VALUE
    );
}
}