#include "application/System/Controllers/AxisController/IAxisController.hpp"
#include "application/System/Controllers/AxisController/XAxisController/XAxisController.hpp"
#include "application/System/Controllers/AxisController/YAxisController/YAxisController.hpp"
#include "application/System/Controllers/AxisController/ZAxisController/ZAxisController.hpp"
#include "application/System/Controllers/PersistentStorageController/PersistentData/AxisPersistentConfig.hpp"
#include "platform/gtest/Mocks/Controllers/AxisMotionControllerMock.hpp"
#include "platform/gtest/Mocks/Controllers/LoggerSinkMock.hpp"
#include "platform/gtest/Mocks/Drivers/LimitSwitchMock.hpp"

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <memory>

using namespace testing;

namespace ATC {

// NOLINTBEGIN (IgnorePublicMemberVariables)

enum class TestedAxis : uint8_t { XAxis, YAxis, ZAxis };
inline std::ostream& operator<<(std::ostream& outputStream, TestedAxis axis) {
    switch (axis) {
    case TestedAxis::XAxis:
        return outputStream << "XAxis";
    case TestedAxis::YAxis:
        return outputStream << "YAxis";
    case TestedAxis::ZAxis:
        return outputStream << "ZAxis";
    }
    return outputStream << "UnknownAxis";
}

class AxisControllerDelegationTest : public TestWithParam<TestedAxis> {
private:
    std::unique_ptr<XAxisController> createXAxisController(
        LoggerSinkMock& loggerSinkMock,
        AxisMotionControllerMock& axisMotionControllerMock
    ) {
        return std::make_unique<XAxisController>(
            loggerSinkMock, axisMotionControllerMock
        );
    }

    LimitSwitchMock limitSwitchMock_ {};

    std::unique_ptr<YAxisController> createYAxisController(
        LoggerSinkMock& loggerSinkMock,
        AxisMotionControllerMock& axisMotionControllerMock
    ) {
        return std::make_unique<YAxisController>(
            loggerSinkMock, axisMotionControllerMock, limitSwitchMock_
        );
    }

    std::unique_ptr<ZAxisController> createZAxisController(
        LoggerSinkMock& loggerSinkMock,
        AxisMotionControllerMock& axisMotionControllerMock
    ) {
        return std::make_unique<ZAxisController>(
            loggerSinkMock, axisMotionControllerMock
        );
    }

public:
    static constexpr AxisPersistentConfig AXIS_PERSISTENT_CONFIG {
        .startPositionInMicrometers = 100,
        .endPositionInMicrometers = 200,
        .speedInMillimetersPerSecond = 20
    };

    LoggerSinkMock loggerSinkMock_ {};
    AxisMotionControllerMock axisMotionControllerMock_ {};

    std::unique_ptr<IAxisController> axisController_;

    void SetUp() override {
        switch (GetParam()) {
        case TestedAxis::XAxis:
            axisController_ = createXAxisController(
                loggerSinkMock_, axisMotionControllerMock_
            );
            break;
        case TestedAxis::YAxis:
            axisController_ = createYAxisController(
                loggerSinkMock_, axisMotionControllerMock_
            );
            break;
        case TestedAxis::ZAxis:
            axisController_ = createZAxisController(
                loggerSinkMock_, axisMotionControllerMock_
            );
            break;
        }
    }
};
// NOLINTEND

INSTANTIATE_TEST_SUITE_P(
    AllAxisControllers,
    AxisControllerDelegationTest,
    Values(TestedAxis::XAxis, TestedAxis::YAxis, TestedAxis::ZAxis)
);

TEST_P(
    AxisControllerDelegationTest,
    GIVEN_AxisController_WHEN_controllerIsInitialized_THEN_axisMotionControllerIsSetUp
) {
    EXPECT_CALL(axisMotionControllerMock_, init());
    EXPECT_CALL(
        axisMotionControllerMock_,
        setMillimetersPerSecond(
            AXIS_PERSISTENT_CONFIG.speedInMillimetersPerSecond
        )
    );

    axisController_->init(AXIS_PERSISTENT_CONFIG);
}

TEST_P(
    AxisControllerDelegationTest,
    GIVEN_AxisController_WHEN_controllerIsTicked_THEN_axisMotionControllerIsTicked
) {
    EXPECT_CALL(axisMotionControllerMock_, tick());

    axisController_->tick();
}

TEST_P(
    AxisControllerDelegationTest,
    GIVEN_AxisController_WHEN_wasFaultReportedIsCalled_THEN_axisMotionControllerFaultIsReturned
) {
    ON_CALL(axisMotionControllerMock_, wasFaultDetected())
        .WillByDefault(Return(true));

    ASSERT_TRUE(axisController_->wasFaultReported());

    ON_CALL(axisMotionControllerMock_, wasFaultDetected())
        .WillByDefault(Return(false));

    ASSERT_FALSE(axisController_->wasFaultReported());
}

TEST_P(
    AxisControllerDelegationTest,
    GIVEN_AxisController_WHEN_moveToPositionIsCalled_THEN_axisMotionControllerIsMoved
) {
    constexpr uint32_t position = 3000;

    EXPECT_CALL(
        axisMotionControllerMock_, moveToPositionInMicrometers(position)
    );

    axisController_->moveToPositionInMicrometers(position);
}

TEST_P(
    AxisControllerDelegationTest,
    GIVEN_AxisController_WHEN_getCurrentPositionIsCalled_THEN_axisMotionControllerPositionIsReturned
) {
    constexpr uint32_t position = 1000;

    EXPECT_CALL(
        axisMotionControllerMock_, getCurrentPositionInMicrometers()
    )
        .WillRepeatedly(Return(position));

    ASSERT_EQ(
        axisMotionControllerMock_.getCurrentPositionInMicrometers(),
        position
    );
}

TEST_P(
    AxisControllerDelegationTest,
    GIVEN_AxisController_WHEN_moveToMinLimitPositionIsCalled_THEN_axisMotionControllerIsMovedToMinLimitSwitch
) {
    EXPECT_CALL(axisMotionControllerMock_, moveToMinLimitSwitch());

    axisController_->moveToMinLimitPosition();
}

TEST_P(
    AxisControllerDelegationTest,
    GIVEN_AxisController_WHEN_isAtMinLimitPositionIsCalled_THEN_axisMotionControllerIsAtMinLimitIsReturned
) {
    EXPECT_CALL(axisMotionControllerMock_, isAtMinLimit())
        .WillOnce(Return(true));

    ASSERT_TRUE(axisController_->isAtMinLimitPosition());

    EXPECT_CALL(axisMotionControllerMock_, isAtMinLimit())
        .WillOnce(Return(false));

    ASSERT_FALSE(axisController_->isAtMinLimitPosition());
}

TEST_P(
    AxisControllerDelegationTest,
    GIVEN_AxisController_WHEN_moveToMaxLimitPositionIsCalled_THEN_axisMotionControllerIsMovedToMaxLimitSwitch
) {
    EXPECT_CALL(axisMotionControllerMock_, moveToMaxLimitSwitch());

    axisController_->moveToMaxLimitPosition();
}

TEST_P(
    AxisControllerDelegationTest,
    GIVEN_AxisController_WHEN_isAtMaxLimitPositionIsCalled_THEN_axisMotionControllerIsAtMaxLimitIsReturned
) {
    EXPECT_CALL(axisMotionControllerMock_, isAtMaxLimit())
        .WillOnce(Return(true));

    ASSERT_TRUE(axisController_->isAtMaxLimitPosition());

    EXPECT_CALL(axisMotionControllerMock_, isAtMaxLimit())
        .WillOnce(Return(false));

    ASSERT_FALSE(axisController_->isAtMaxLimitPosition());
}

TEST_P(
    AxisControllerDelegationTest,
    GIVEN_AxisController_WHEN_moveToHomePositionIsCalled_THEN_axisMotionControllerIsHomedIsReturned
) {
    EXPECT_CALL(axisMotionControllerMock_, homeAxis());

    axisController_->moveToHomePosition();
}

TEST_P(
    AxisControllerDelegationTest,
    GIVEN_AxisController_WHEN_isAtHomePositionIsCalled_THEN_axisMotionControllerIsAtMinLimitIsReturned
) {
    EXPECT_CALL(axisMotionControllerMock_, isAtMinLimit())
        .WillOnce(Return(true));

    ASSERT_TRUE(axisController_->isAtHomePosition());

    EXPECT_CALL(axisMotionControllerMock_, isAtMinLimit())
        .WillOnce(Return(false));

    ASSERT_FALSE(axisController_->isAtHomePosition());
}

TEST_P(
    AxisControllerDelegationTest,
    GIVEN_AxisController_WHEN_moveToStartPositionIsCalled_THEN_axisMotionControllerIsMoved
) {
    EXPECT_CALL(
        axisMotionControllerMock_,
        moveToPositionInMicrometers(
            AXIS_PERSISTENT_CONFIG.startPositionInMicrometers
        )
    );

    axisController_->init(AXIS_PERSISTENT_CONFIG);
    axisController_->moveToStartPosition();
}

TEST_P(
    AxisControllerDelegationTest,
    GIVEN_AxisController_WHEN_isAtStartPositionIsCalled_THEN_axisMotionControllerIsAtPositionIsReturned
) {
    axisController_->init(AXIS_PERSISTENT_CONFIG);

    EXPECT_CALL(
        axisMotionControllerMock_,
        isAtPositionInMicrometers(
            AXIS_PERSISTENT_CONFIG.startPositionInMicrometers
        )
    )
        .WillOnce(Return(true));

    ASSERT_TRUE(axisController_->isAtStartPosition());

    EXPECT_CALL(
        axisMotionControllerMock_,
        isAtPositionInMicrometers(
            AXIS_PERSISTENT_CONFIG.startPositionInMicrometers
        )
    )
        .WillOnce(Return(false));

    ASSERT_FALSE(axisController_->isAtStartPosition());
}

TEST_P(
    AxisControllerDelegationTest,
    GIVEN_AxisController_WHEN_moveToEndPositionIsCalled_THEN_axisMotionControllerIsMoved
) {
    EXPECT_CALL(
        axisMotionControllerMock_,
        moveToPositionInMicrometers(
            AXIS_PERSISTENT_CONFIG.endPositionInMicrometers
        )
    );

    axisController_->init(AXIS_PERSISTENT_CONFIG);
    axisController_->moveToEndPosition();
}

TEST_P(
    AxisControllerDelegationTest,
    GIVEN_AxisController_WHEN_isAtEndPositionIsCalled_THEN_axisMotionControllerIsAtPositionIsReturned
) {
    axisController_->init(AXIS_PERSISTENT_CONFIG);

    EXPECT_CALL(
        axisMotionControllerMock_,
        isAtPositionInMicrometers(
            AXIS_PERSISTENT_CONFIG.endPositionInMicrometers
        )
    )
        .WillOnce(Return(true));

    ASSERT_TRUE(axisController_->isAtEndPosition());

    EXPECT_CALL(
        axisMotionControllerMock_,
        isAtPositionInMicrometers(
            AXIS_PERSISTENT_CONFIG.endPositionInMicrometers
        )
    )
        .WillOnce(Return(false));

    ASSERT_FALSE(axisController_->isAtEndPosition());
}

TEST_P(
    AxisControllerDelegationTest,
    GIVEN_AxisController_WHEN_setStartPositionIsCalled_THEN_startPositionIsSet
) {
    constexpr uint32_t newPosition =
        AXIS_PERSISTENT_CONFIG.startPositionInMicrometers + 2000;

    axisController_->init(AXIS_PERSISTENT_CONFIG);
    axisController_->setStartPositionInMicrometers(newPosition);

    EXPECT_CALL(
        axisMotionControllerMock_,
        moveToPositionInMicrometers(newPosition)
    );
    axisController_->moveToStartPosition();

    ASSERT_EQ(
        axisController_->getStartPositionInMicrometers(), newPosition
    );
}

TEST_P(
    AxisControllerDelegationTest,
    GIVEN_AxisController_WHEN_setEndPositionIsCalled_THEN_endPositionIsSet
) {
    constexpr uint32_t newPosition =
        AXIS_PERSISTENT_CONFIG.endPositionInMicrometers + 2000;

    axisController_->init(AXIS_PERSISTENT_CONFIG);
    axisController_->setEndPositionInMicrometers(newPosition);

    EXPECT_CALL(
        axisMotionControllerMock_,
        moveToPositionInMicrometers(newPosition)
    );
    axisController_->moveToEndPosition();

    ASSERT_EQ(
        axisController_->getEndPositionInMicrometers(), newPosition
    );
}

TEST_P(
    AxisControllerDelegationTest,
    GIVEN_AxisController_WHEN_setSpeedIsCalled_THEN_axisMotionControllerSpeedIsSet
) {
    constexpr uint32_t newSpeed =
        AXIS_PERSISTENT_CONFIG.speedInMillimetersPerSecond + 10;

    axisController_->init(AXIS_PERSISTENT_CONFIG);

    EXPECT_CALL(
        axisMotionControllerMock_, setMillimetersPerSecond(newSpeed)
    );
    ON_CALL(axisMotionControllerMock_, getMillimetersPerSecond())
        .WillByDefault(Return(newSpeed));

    axisController_->setSpeedInMillimetersPerSecond(newSpeed);
    ASSERT_EQ(
        axisController_->getSpeedInMillimetersPerSecond(), newSpeed
    );
}

TEST_P(
    AxisControllerDelegationTest,
    GIVEN_AxisController_WHEN_cancelMovementIsCalled_THEN_motionControllerMovementIsCanceled
) {
    EXPECT_CALL(axisMotionControllerMock_, cancelMovement());

    axisController_->cancelMovement();
}
}