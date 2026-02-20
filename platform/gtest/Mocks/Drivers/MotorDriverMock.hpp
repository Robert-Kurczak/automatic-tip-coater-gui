#pragma once

#include "application/System/Drivers/MotorDriver/IMotorDriver.hpp"

#include "gmock/gmock.h"

namespace ATC {
class MotorDriverMock : public IMotorDriver {
public:
    MOCK_METHOD(void, init, (), (override));

    MOCK_METHOD(void, startRotation, (uint8_t), (override));

    MOCK_METHOD(void, stopRotation, (), (override));

    MOCK_METHOD(void, setDirectionClockwise, (), (override));

    MOCK_METHOD(void, setDirectionCounterClockwise, (), (override));

    MOCK_METHOD(bool, isDirectionClockwise, (), (const override));

    MOCK_METHOD(bool, isFaultDetected, (), (override));
};
}