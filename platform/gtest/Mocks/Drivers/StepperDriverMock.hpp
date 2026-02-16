#pragma once

#include "application/System/Drivers/StepperDriver/IStepperDriver.hpp"

#include "gmock/gmock.h"

using namespace testing;

namespace ATC {
class StepperDriverMock : public IStepperDriver {
public:
    MOCK_METHOD(void, init, (), (override));

    MOCK_METHOD(void, startStepping, (), (override));

    MOCK_METHOD(void, stopStepping, (), (override));

    MOCK_METHOD(
        void,
        setMicrosecondsBetweenStepToggle,
        (uint32_t),
        (override)
    );

    MOCK_METHOD(void, setDirectionClockwise, (), (override));

    MOCK_METHOD(void, setDirectionCounterClockwise, (), (override));

    MOCK_METHOD(bool, isFaultDetected, (), (const override));
};
}