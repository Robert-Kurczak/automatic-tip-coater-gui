#include "application/System/Services/AxisConfiguratorService/AxisConfiguratorService.hpp"

#include "application/System/Controllers/PersistentStorageController/PersistentData/AxisPersistentConfig.hpp"
#include "application/System/Services/AxisConfiguratorService/AxisConfiguratorParameters.hpp"
#include "application/System/Services/AxisConfiguratorService/XAxisConfiguratorService/XAxisConfiguratorService.hpp"
#include "application/System/Services/AxisConfiguratorService/YAxisConfiguratorService/YAxisConfiguratorService.hpp"
#include "application/System/Services/AxisConfiguratorService/ZAxisConfiguratorService/ZAxisConfiguratorService.hpp"
#include "platform/gtest/Mocks/Controllers/AxisControllerMock.hpp"
#include "platform/gtest/Mocks/Controllers/PersistentStorageControllerMock.hpp"

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <memory>

using namespace testing;
enum class TestedAxis : uint8_t { XAxis, YAxis, ZAxis };
inline std::ostream& operator<<(
    std::ostream& outputStream,
    TestedAxis axis
) {
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

namespace ATC {
class AxisConfiguratorServiceTest : public TestWithParam<TestedAxis> {
public:
    static constexpr AxisConfiguratorParameters PARAMETERS {
        .positionStepInMicrometers = 5,
        .speedStepInMillimetersPerSecond = 1,
        .speedShowcasePositionInMicrometers = 200,
        .minPositionInMicrometers = 10,
        .maxPositionInMicrometers = 1000,
        .minSpeedInMillimetersPerSecond = 3,
        .maxSpeedInMillimetersPerSecond = 300,
    };

    static constexpr uint32_t START_POSITION =
        PARAMETERS.minPositionInMicrometers + 100;

    static constexpr uint32_t END_POSITION =
        PARAMETERS.maxPositionInMicrometers - 100;

    static constexpr uint32_t SPEED =
        PARAMETERS.maxSpeedInMillimetersPerSecond - 10;

    PersistentStorageControllerMock persistentStorageControllerMock_ {};
    AxisControllerMock axisControllerMock_ {};

    std::unique_ptr<AxisConfiguratorService> axisConfiguratorService_;

    void setBufferedConfig() const {
        EXPECT_CALL(axisControllerMock_, getStartPositionInMicrometers())
            .WillOnce(Return(START_POSITION));

        EXPECT_CALL(axisControllerMock_, getEndPositionInMicrometers())
            .WillOnce(Return(END_POSITION));

        EXPECT_CALL(axisControllerMock_, getSpeedInMillimetersPerSecond())
            .WillOnce(Return(SPEED));

        axisConfiguratorService_->resetBufferedConfig();
    }

    AxisConfiguratorServiceTest() {
        switch (GetParam()) {
        case TestedAxis::XAxis:
            axisConfiguratorService_ = createXAxisConfiguratorService();
            break;
        case TestedAxis::YAxis:
            axisConfiguratorService_ = createYAxisConfiguratorService();
            break;
        case TestedAxis::ZAxis:
            axisConfiguratorService_ = createZAxisConfiguratorService();
            break;
        }
    }

private:
    std::unique_ptr<XAxisConfiguratorService>
    createXAxisConfiguratorService() {
        return std::make_unique<XAxisConfiguratorService>(
            persistentStorageControllerMock_,
            axisControllerMock_,
            PARAMETERS
        );
    }

    std::unique_ptr<YAxisConfiguratorService>
    createYAxisConfiguratorService() {
        return std::make_unique<YAxisConfiguratorService>(
            persistentStorageControllerMock_,
            axisControllerMock_,
            PARAMETERS
        );
    }

    std::unique_ptr<ZAxisConfiguratorService>
    createZAxisConfiguratorService() {
        return std::make_unique<ZAxisConfiguratorService>(
            persistentStorageControllerMock_,
            axisControllerMock_,
            PARAMETERS
        );
    }
};

INSTANTIATE_TEST_SUITE_P(
    AllAxisConfigurators,
    AxisConfiguratorServiceTest,
    Values(TestedAxis::XAxis, TestedAxis::YAxis, TestedAxis::ZAxis)
);

TEST_P(
    AxisConfiguratorServiceTest,
    GIVEN_axisConfiguratorService_WHEN_resetBufferedConfigIsCalled_THEN_configsAreReadFromController
) {
    setBufferedConfig();

    ASSERT_EQ(
        axisConfiguratorService_->getStartPositionInMicrometers(),
        START_POSITION
    );

    ASSERT_EQ(
        axisConfiguratorService_->getEndPositionInMicrometers(),
        END_POSITION
    );

    ASSERT_EQ(
        axisConfiguratorService_->getSpeedInMillimetersPerSecond(), SPEED
    );
}

TEST_P(
    AxisConfiguratorServiceTest,
    GIVEN_axisConfiguratorService_WHEN_showcaseStartPositionIsCalled_THEN_axisControllerIsMovedToPosition
) {
    setBufferedConfig();

    EXPECT_CALL(
        axisControllerMock_, moveToPositionInMicrometers(START_POSITION)
    );

    axisConfiguratorService_->showcaseStartPosition();
}

TEST_P(
    AxisConfiguratorServiceTest,
    GIVEN_axisConfiguratorService_WHEN_increaseStartPositionIsCalled_THEN_positionIsShowcased
) {
    setBufferedConfig();

    EXPECT_CALL(
        axisControllerMock_,
        moveToPositionInMicrometers(
            START_POSITION + PARAMETERS.positionStepInMicrometers
        )
    );

    axisConfiguratorService_->increaseStartPosition();
}

TEST_P(
    AxisConfiguratorServiceTest,
    GIVEN_axisConfiguratorService_WHEN_increaseStartPositionIsCalled_THEN_positionDoesNotExceedEndPosition
) {
    setBufferedConfig();

    constexpr uint32_t increments =
        ((END_POSITION - START_POSITION) /
         PARAMETERS.positionStepInMicrometers) +
        10;

    EXPECT_CALL(
        axisControllerMock_, moveToPositionInMicrometers(Le(END_POSITION))
    )
        .Times(AnyNumber());

    for (uint32_t i = 0; i < increments; i++) {
        axisConfiguratorService_->increaseStartPosition();
    }

    ASSERT_EQ(
        axisConfiguratorService_->getStartPositionInMicrometers(),
        END_POSITION
    );
}

TEST_P(
    AxisConfiguratorServiceTest,
    GIVEN_axisConfiguratorService_WHEN_decreaseStartPositionIsCalled_THEN_positionIsShowcased
) {
    setBufferedConfig();

    EXPECT_CALL(
        axisControllerMock_,
        moveToPositionInMicrometers(
            START_POSITION - PARAMETERS.positionStepInMicrometers
        )
    );

    axisConfiguratorService_->decreaseStartPosition();
}

TEST_P(
    AxisConfiguratorServiceTest,
    GIVEN_axisConfiguratorService_WHEN_decreaseStartPositionIsCalled_THEN_positionDoesNotExceedMinPosition
) {
    setBufferedConfig();

    constexpr uint32_t decrements =
        ((START_POSITION - PARAMETERS.minPositionInMicrometers) /
         PARAMETERS.positionStepInMicrometers) +
        10;

    EXPECT_CALL(
        axisControllerMock_,
        moveToPositionInMicrometers(
            Ge(PARAMETERS.minPositionInMicrometers)
        )
    )
        .Times(AnyNumber());

    for (uint32_t i = 0; i < decrements; i++) {
        axisConfiguratorService_->decreaseStartPosition();
    }

    ASSERT_EQ(
        axisConfiguratorService_->getStartPositionInMicrometers(),
        PARAMETERS.minPositionInMicrometers
    );
}

TEST_P(
    AxisConfiguratorServiceTest,
    GIVEN_axisConfiguratorService_WHEN_saveStartPositionIsCalled_THEN_controllerPositionIsUpdated
) {
    setBufferedConfig();

    axisConfiguratorService_->increaseStartPosition();

    EXPECT_CALL(
        axisControllerMock_,
        setStartPositionInMicrometers(
            START_POSITION + PARAMETERS.positionStepInMicrometers
        )
    );

    axisConfiguratorService_->saveStartPosition();
}

TEST_P(
    AxisConfiguratorServiceTest,
    GIVEN_axisConfiguratorService_WHEN_showcaseEndPositionIsCalled_THEN_axisControllerIsMovedToPosition
) {
    setBufferedConfig();

    EXPECT_CALL(
        axisControllerMock_, moveToPositionInMicrometers(END_POSITION)
    );

    axisConfiguratorService_->showcaseEndPosition();
}

TEST_P(
    AxisConfiguratorServiceTest,
    GIVEN_axisConfiguratorService_WHEN_increaseEndPositionIsCalled_THEN_positionIsShowcased
) {
    setBufferedConfig();

    EXPECT_CALL(
        axisControllerMock_,
        moveToPositionInMicrometers(
            END_POSITION + PARAMETERS.positionStepInMicrometers
        )
    );

    axisConfiguratorService_->increaseEndPosition();
}

TEST_P(
    AxisConfiguratorServiceTest,
    GIVEN_axisConfiguratorService_WHEN_increaseEndPositionIsCalled_THEN_positionDoesNotExceedMaxPosition
) {
    setBufferedConfig();

    constexpr uint32_t increments =
        ((PARAMETERS.maxPositionInMicrometers - END_POSITION) /
         PARAMETERS.positionStepInMicrometers) +
        10;

    EXPECT_CALL(
        axisControllerMock_,
        moveToPositionInMicrometers(
            Le(PARAMETERS.maxPositionInMicrometers)
        )
    )
        .Times(AnyNumber());

    for (uint32_t i = 0; i < increments; i++) {
        axisConfiguratorService_->increaseEndPosition();
    }

    ASSERT_EQ(
        axisConfiguratorService_->getEndPositionInMicrometers(),
        PARAMETERS.maxPositionInMicrometers
    );
}

TEST_P(
    AxisConfiguratorServiceTest,
    GIVEN_axisConfiguratorService_WHEN_decreaseEndPositionIsCalled_THEN_positionIsShowcased
) {
    setBufferedConfig();

    EXPECT_CALL(
        axisControllerMock_,
        moveToPositionInMicrometers(
            END_POSITION - PARAMETERS.positionStepInMicrometers
        )
    );

    axisConfiguratorService_->decreaseEndPosition();
}

TEST_P(
    AxisConfiguratorServiceTest,
    GIVEN_axisConfiguratorService_WHEN_decreaseEndPositionIsCalled_THEN_positionDoesNotExceedStartPosition
) {
    setBufferedConfig();

    constexpr uint32_t decrements =
        ((END_POSITION - START_POSITION) /
         PARAMETERS.positionStepInMicrometers) +
        10;

    EXPECT_CALL(
        axisControllerMock_,
        moveToPositionInMicrometers(Ge(START_POSITION))
    )
        .Times(AnyNumber());

    for (uint32_t i = 0; i < decrements; i++) {
        axisConfiguratorService_->decreaseEndPosition();
    }

    ASSERT_EQ(
        axisConfiguratorService_->getEndPositionInMicrometers(),
        START_POSITION
    );
}

TEST_P(
    AxisConfiguratorServiceTest,
    GIVEN_axisConfiguratorService_WHEN_saveEndPositionIsCalled_THEN_controllerPositionIsUpdated
) {
    setBufferedConfig();

    axisConfiguratorService_->increaseEndPosition();

    EXPECT_CALL(
        axisControllerMock_,
        setEndPositionInMicrometers(
            END_POSITION + PARAMETERS.positionStepInMicrometers
        )
    );

    axisConfiguratorService_->saveEndPosition();
}

TEST_P(
    AxisConfiguratorServiceTest,
    GIVEN_axisConfiguratorService_WHEN_showcaseSpeedIsCalled_THEN_axisControllerIsMovedToPosition
) {
    setBufferedConfig();

    EXPECT_CALL(axisControllerMock_, getCurrentPositionInMicrometers())
        .WillOnce(Return(END_POSITION));

    EXPECT_CALL(
        axisControllerMock_,
        moveToPositionInMicrometers(
            PARAMETERS.speedShowcasePositionInMicrometers
        )
    );

    axisConfiguratorService_->showcaseSpeed();
}

TEST_P(
    AxisConfiguratorServiceTest,
    GIVEN_axisConfiguratorService_WHEN_showcaseSpeedIsCalledWhileAxisIsAtShowcasePosition_THEN_axisControllerIsMovedToStartPosition
) {
    setBufferedConfig();

    EXPECT_CALL(axisControllerMock_, getCurrentPositionInMicrometers())
        .WillOnce(Return(PARAMETERS.speedShowcasePositionInMicrometers));

    EXPECT_CALL(axisControllerMock_, moveToStartPosition());

    axisConfiguratorService_->showcaseSpeed();
}

TEST_P(
    AxisConfiguratorServiceTest,
    GIVEN_axisConfiguratorService_WHEN_increaseSpeedIsCalled_THEN_speedDoesNotExceedMaxValue
) {
    setBufferedConfig();

    constexpr uint32_t increments =
        ((PARAMETERS.maxSpeedInMillimetersPerSecond - SPEED) /
         PARAMETERS.speedStepInMillimetersPerSecond) +
        10;

    for (uint32_t i = 0; i < increments; i++) {
        axisConfiguratorService_->increaseSpeed();
    }

    ASSERT_EQ(
        axisConfiguratorService_->getSpeedInMillimetersPerSecond(),
        PARAMETERS.maxSpeedInMillimetersPerSecond
    );
}

TEST_P(
    AxisConfiguratorServiceTest,
    GIVEN_axisConfiguratorService_WHEN_decreaseSpeedIsCalled_THEN_positionDoesNotExceedMinValue
) {
    setBufferedConfig();

    constexpr uint32_t decrements =
        ((SPEED - PARAMETERS.minSpeedInMillimetersPerSecond) /
         PARAMETERS.speedStepInMillimetersPerSecond) +
        10;

    for (uint32_t i = 0; i < decrements; i++) {
        axisConfiguratorService_->decreaseSpeed();
    }

    ASSERT_EQ(
        axisConfiguratorService_->getSpeedInMillimetersPerSecond(),
        PARAMETERS.minSpeedInMillimetersPerSecond
    );
}

TEST_P(
    AxisConfiguratorServiceTest,
    GIVEN_axisConfiguratorService_WHEN_saveSpeedIsCalled_THEN_controllerSpeedIsUpdated
) {
    setBufferedConfig();

    axisConfiguratorService_->increaseSpeed();

    EXPECT_CALL(
        axisControllerMock_,
        setSpeedInMillimetersPerSecond(
            SPEED + PARAMETERS.speedStepInMillimetersPerSecond
        )
    );

    axisConfiguratorService_->saveSpeed();
}

TEST_P(
    AxisConfiguratorServiceTest,
    GIVEN_axisConfiguratorService_WHEN_saveSpeedIsCalled_THEN_speedIsShowcased
) {
    setBufferedConfig();

    axisConfiguratorService_->increaseSpeed();

    EXPECT_CALL(axisControllerMock_, getCurrentPositionInMicrometers())
        .WillOnce(Return(START_POSITION));

    EXPECT_CALL(
        axisControllerMock_,
        moveToPositionInMicrometers(
            PARAMETERS.speedShowcasePositionInMicrometers
        )
    );

    axisConfiguratorService_->saveSpeed();
}

TEST_P(
    AxisConfiguratorServiceTest,
    GIVEN_axisConfiguratorService_WHEN_getStoredConfigIsCalled_THEN_controllerConfigIsReturned
) {
    EXPECT_CALL(axisControllerMock_, getStartPositionInMicrometers())
        .WillOnce(Return(START_POSITION));

    EXPECT_CALL(axisControllerMock_, getEndPositionInMicrometers())
        .WillOnce(Return(END_POSITION));

    EXPECT_CALL(axisControllerMock_, getSpeedInMillimetersPerSecond())
        .WillOnce(Return(SPEED));

    const AxisPersistentConfig config =
        axisConfiguratorService_->getStoredConfig();

    ASSERT_EQ(config.startPositionInMicrometers, START_POSITION);
    ASSERT_EQ(config.endPositionInMicrometers, END_POSITION);
    ASSERT_EQ(config.speedInMillimetersPerSecond, SPEED);
}
}