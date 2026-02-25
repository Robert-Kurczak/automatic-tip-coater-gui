#include "application/System/Tasks/Task/HeaterTestTask/HeaterTestTask.hpp"

#include "application/System/Tasks/Task/HeaterTestTask/HeaterTestResults.hpp"
#include "platform/gtest/Mocks/Controllers/HeaterControllerMock.hpp"
#include "platform/gtest/Mocks/Ports/SystemClockMock.hpp"

#include "gtest/gtest.h"

using namespace testing;

namespace ATC {
class HeaterTestTaskTest : public Test {
public:
    static constexpr uint8_t TICK_AMOUNT = 100;

    static constexpr uint32_t HEATING_TIMEOUT_IN_MILLIS = 8000;
    HeaterControllerMock heaterControllerMock_ {};
    SystemClockMock systemClockMock_ {};

    HeaterTestTask heaterTestTask_ {
        heaterControllerMock_,
        systemClockMock_,
        HEATING_TIMEOUT_IN_MILLIS
    };

    void expectClockSimulation() {
        EXPECT_CALL(systemClockMock_, getMillisecondsSinceStart())
            .WillRepeatedly([]() {
                constexpr uint32_t millisBetweenCalls = 100;
                static uint32_t calls = 0;

                calls++;

                return millisBetweenCalls * calls;
            });
    }
};

TEST_F(
    HeaterTestTaskTest,
    GIVEN_heaterTestTask_WHEN_taskIsNotStarted_THEN_taskIdlesWhenTicked
) {
    EXPECT_CALL(heaterControllerMock_, turnOn()).Times(0);

    for (uint8_t i = 0; i < TICK_AMOUNT; i++) {
        heaterTestTask_.tick();
    }
}

TEST_F(
    HeaterTestTaskTest,
    GIVEN_heaterTestTask_WHEN_taskIsStarted_THEN_heaterIsTurnOn
) {
    EXPECT_CALL(heaterControllerMock_, turnOn());

    heaterTestTask_.start();

    for (uint8_t i = 0; i < TICK_AMOUNT; i++) {
        heaterTestTask_.tick();
    }
}

TEST_F(
    HeaterTestTaskTest,
    GIVEN_heaterTestTask_WHEN_heaterReachesTargetTemperature_THEN_heaterIsTurnedOff
) {
    {
        InSequence sequence;

        EXPECT_CALL(heaterControllerMock_, isAtTargetTemperature())
            .WillOnce(Return(false))
            .WillOnce(Return(false))
            .WillOnce(Return(true));

        EXPECT_CALL(heaterControllerMock_, turnOff());
    }

    heaterTestTask_.start();

    for (uint8_t i = 0; i < TICK_AMOUNT; i++) {
        heaterTestTask_.tick();
    }
}

TEST_F(
    HeaterTestTaskTest,
    GIVEN_heaterTestTask_WHEN_heaterIsTurnedOff_THEN_taskIsFinished
) {
    EXPECT_CALL(heaterControllerMock_, isAtTargetTemperature())
        .WillRepeatedly(Return(true));
    EXPECT_CALL(heaterControllerMock_, turnOff());

    heaterTestTask_.start();

    ASSERT_FALSE(heaterTestTask_.isFinished());

    for (uint8_t i = 0; i < TICK_AMOUNT; i++) {
        heaterTestTask_.tick();
    }

    ASSERT_TRUE(heaterTestTask_.isFinished());
}

TEST_F(
    HeaterTestTaskTest,
    GIVEN_heaterTestTask_WHEN_waitingForTargetTemperatureTimesOut_THEN_temperatureFailureIsReported
) {
    EXPECT_CALL(heaterControllerMock_, isAtTargetTemperature())
        .WillRepeatedly(Return(false));

    expectClockSimulation();

    heaterTestTask_.start();

    for (uint8_t i = 0; i < TICK_AMOUNT; i++) {
        heaterTestTask_.tick();
    }

    ASSERT_TRUE(heaterTestTask_.isFinished());
    const HeaterTestResults results = heaterTestTask_.consumeResult();

    ASSERT_FALSE(results.temperatureSuccess);
}

TEST_F(
    HeaterTestTaskTest,
    GIVEN_heaterTestTask_WHEN_heaterReachesTargetTemperature_THEN_temperatureSuccessIsReported
) {
    EXPECT_CALL(heaterControllerMock_, isAtTargetTemperature())
        .WillRepeatedly(Return(true));

    heaterTestTask_.start();

    for (uint8_t i = 0; i < TICK_AMOUNT; i++) {
        heaterTestTask_.tick();
    }

    ASSERT_TRUE(heaterTestTask_.isFinished());
    const HeaterTestResults results = heaterTestTask_.consumeResult();

    ASSERT_TRUE(results.temperatureSuccess);
}

TEST_F(
    HeaterTestTaskTest,
    GIVEN_heaterTestTask_WHEN_taskIsReset_THEN_heaterIsTurnedOff
) {
    heaterTestTask_.start();

    EXPECT_CALL(heaterControllerMock_, turnOff());

    heaterTestTask_.reset();
}

TEST_F(
    HeaterTestTaskTest,
    GIVEN_heaterTestTask_WHEN_resultIsConsumed_THEN_resultsAreReset
) {
    EXPECT_CALL(heaterControllerMock_, isAtTargetTemperature())
        .WillRepeatedly(Return(true));

    heaterTestTask_.start();

    for (uint8_t i = 0; i < TICK_AMOUNT; i++) {
        heaterTestTask_.tick();
    }

    ASSERT_TRUE(heaterTestTask_.isFinished());

    const HeaterTestResults successfulResults =
        heaterTestTask_.consumeResult();

    const HeaterTestResults cleanedResults =
        heaterTestTask_.consumeResult();

    ASSERT_FALSE(cleanedResults.temperatureSuccess);
}
}