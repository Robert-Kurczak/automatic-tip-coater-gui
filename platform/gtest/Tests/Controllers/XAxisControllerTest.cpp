#include "application/System/Controllers/AxisController/XAxisController/XAxisController.hpp"

#include "application/System/Controllers/PersistentStorageController/PersistentData/AxisPersistentConfig.hpp"
#include "platform/gtest/Mocks/Controllers/AxisMotionControllerMock.hpp"
#include "platform/gtest/Mocks/Controllers/LoggerSinkMock.hpp"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

using namespace testing;

namespace ATC {
class XAxisControllerTest : public Test {
public:
    static constexpr AxisPersistentConfig AXIS_PERSISTENT_CONFIG {
        .startPositionInMicrometers = 1000,
        .endPositionInMicrometers = 2000,
        .speedInMillimetersPerSecond = 300
    };

    LoggerSinkMock loggerSinkMock_ {};
    AxisMotionControllerMock axisMotionControllerMock_ {};

    XAxisController xAxisController_ {
        loggerSinkMock_,
        axisMotionControllerMock_
    };
};

TEST_F(
    XAxisControllerTest,
    GIVEN_xAxisController_WHEN_moveToHeaterFronPositionIsCalled_THEN_axisMotionControllerIsMoved
) {
    xAxisController_.init(AXIS_PERSISTENT_CONFIG);

    constexpr float offsetFactor = 0.8;

    EXPECT_CALL(
        axisMotionControllerMock_,
        moveToPositionInMicrometers(
            AXIS_PERSISTENT_CONFIG.endPositionInMicrometers * offsetFactor
        )
    );

    xAxisController_.moveToHeaterFrontPosition();
}

TEST_F(
    XAxisControllerTest,
    GIVEN_xAxisController_WHEN_isAtHeaterFrontPositionIsCalled_THEN_axisMotionControlerPositionIsChecked
) {
    xAxisController_.init(AXIS_PERSISTENT_CONFIG);

    constexpr float offsetFactor = 0.8;

    EXPECT_CALL(
        axisMotionControllerMock_,
        isAtPositionInMicrometers(
            AXIS_PERSISTENT_CONFIG.endPositionInMicrometers * offsetFactor
        )
    )
        .WillOnce(Return(true))
        .WillOnce(Return(false));

    ASSERT_TRUE(xAxisController_.isAtHeaterFrontPosition());
    ASSERT_FALSE(xAxisController_.isAtHeaterFrontPosition());
}
}