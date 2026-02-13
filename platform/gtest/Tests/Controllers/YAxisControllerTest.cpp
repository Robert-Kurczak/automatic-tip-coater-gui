#include "application/System/Controllers/AxisController/YAxisController/YAxisController.hpp"

#include "platform/gtest/Mocks/Controllers/AxisMotionControllerMock.hpp"
#include "platform/gtest/Mocks/Controllers/LoggerSinkMock.hpp"
#include "platform/gtest/Mocks/Drivers/LimitSwitchMock.hpp"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

using namespace testing;

namespace ATC {
class YAxisControllerTest : public Test {
public:
    static constexpr uint32_t COATING_POSITION_MARGIN_IN_MICROMETERS =
        200;

    LoggerSinkMock loggerSinkMock_ {};
    AxisMotionControllerMock axisMotionControllerMock_ {};
    LimitSwitchMock limitSwitchMock_ {};

    YAxisController yAxisController_ {
        loggerSinkMock_,
        axisMotionControllerMock_,
        limitSwitchMock_
    };
};

TEST_F(
    YAxisControllerTest,
    GIVEN_yAxisController_WHEN_moveToDetectTipIsCalled_THEN_axisMotionControllerIsMovedToMaxLimitSwitch
) {
    EXPECT_CALL(axisMotionControllerMock_, moveToMaxLimitSwitch());

    yAxisController_.moveToDetectTip();
}

TEST_F(
    YAxisControllerTest,
    GIVEN_yAxisController_WHEN_tipIsDetected_THEN_axisMotionMovementIsCanceled
) {
    {
        InSequence sequence;

        EXPECT_CALL(limitSwitchMock_, isActive())
            .WillOnce(Return(false))
            .WillOnce(Return(false))
            .WillOnce(Return(true));

        EXPECT_CALL(axisMotionControllerMock_, cancelMovement());
    }

    yAxisController_.moveToDetectTip();

    for (int i = 0; i < 3; i++) {
        yAxisController_.tick();
    }
}

TEST_F(
    YAxisControllerTest,
    GIVEN_yAxisController_WHEN_tipIsDetected_THEN_coatingPositionIsUpdated
) {
    constexpr uint32_t positionInMicrometers = 1000;

    EXPECT_CALL(limitSwitchMock_, isActive())
        .WillRepeatedly(Return(true));
    EXPECT_CALL(
        axisMotionControllerMock_, getCurrentPositionInMicrometers()
    )
        .WillRepeatedly(Return(positionInMicrometers));

    yAxisController_.moveToDetectTip();
    yAxisController_.tick();

    ASSERT_TRUE(yAxisController_.isTipDetected());

    EXPECT_CALL(
        axisMotionControllerMock_,
        moveToPositionInMicrometers(AllOf(
            Ge(positionInMicrometers -
               (COATING_POSITION_MARGIN_IN_MICROMETERS / 2)),
            Le(positionInMicrometers +
               (COATING_POSITION_MARGIN_IN_MICROMETERS / 2))
        ))
    );
    yAxisController_.moveToCoatingPosition();
}

TEST_F(
    YAxisControllerTest,
    GIVEN_yAxisController_WHEN_isAtCoatingPositionIsCalled_THEN_axisMotionControllerPositionIsChecked
) {
    constexpr uint32_t position = 2000;

    EXPECT_CALL(limitSwitchMock_, isActive()).WillOnce(Return(true));
    EXPECT_CALL(
        axisMotionControllerMock_, getCurrentPositionInMicrometers()
    )
        .WillOnce(Return(position));

    yAxisController_.moveToDetectTip();
    yAxisController_.tick();

    EXPECT_CALL(
        axisMotionControllerMock_,
        isAtPositionInMicrometers(AnyOf(
            Ge(position - (COATING_POSITION_MARGIN_IN_MICROMETERS / 2)),
            Le(position + (COATING_POSITION_MARGIN_IN_MICROMETERS / 2))
        ))
    )
        .WillOnce(Return(true))
        .WillOnce(Return(false));

    ASSERT_TRUE(yAxisController_.isAtCoatingPosition());
    ASSERT_FALSE(yAxisController_.isAtCoatingPosition());
}
}