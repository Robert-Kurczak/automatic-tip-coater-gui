#pragma once

#include "application/System/Controllers/SpindleController/ISpindleController.hpp"

#include "gmock/gmock.h"

using namespace testing;

namespace ATC {
class SpindleControllerMock : public ISpindleController {
public:
    MOCK_METHOD(
        void,
        init,
        (const SpindlePersistentConfig& config),
        (override)
    );

    MOCK_METHOD(void, tick, (), (override));

    MOCK_METHOD(bool, wasFaultReported, (), (override));

    MOCK_METHOD(void, startRotation, (), (override));

    MOCK_METHOD(
        void,
        startTimedRotation,
        (uint32_t rotationMillis),
        (override)
    );

    MOCK_METHOD(void, startTimedRotation, (), (override));

    MOCK_METHOD(void, stopRotation, (), (override));

    MOCK_METHOD(bool, isTimedRotationFinished, (), (const override));

    MOCK_METHOD(void, setDirectionClockwise, (), (override));

    MOCK_METHOD(void, setDirectionCounterClockwise, (), (override));

    MOCK_METHOD(bool, isDirectionClockwise, (), (const override));

    MOCK_METHOD(void, setSpeedPercent, (uint8_t value), (override));

    MOCK_METHOD(uint8_t, getSpeedPercent, (), (const override));

    MOCK_METHOD(
        void,
        setRotationTimeInMillis,
        (uint32_t value),
        (override)
    );

    MOCK_METHOD(uint32_t, getRotationTimeInMillis, (), (const override));
};
}