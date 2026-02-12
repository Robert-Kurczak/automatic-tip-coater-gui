#pragma once

#include "application/System/Controllers/AxisMotionController/IAxisMotionController.hpp"

#include "gmock/gmock.h"

using namespace testing;

namespace ATC {
class AxisMotionControllerMock : public IAxisMotionController {
public:
    MOCK_METHOD(void, init, (), (override));
    MOCK_METHOD(void, tick, (), (override));

    MOCK_METHOD(void, handleStepPulseInterrupt, (), (override));
    MOCK_METHOD(void, handleMinLimitSwitchInterrupt, (), (override));
    MOCK_METHOD(void, handleMaxLimitSwitchInterrupt, (), (override));

    MOCK_METHOD(bool, wasFaultDetected, (), (const override));

    MOCK_METHOD(void, setMillimetersPerSecond, (uint16_t), (override));
    MOCK_METHOD(uint16_t, getMillimetersPerSecond, (), (const override));

    MOCK_METHOD(
        void,
        moveToPositionInMicrometers,
        (uint32_t),
        (override)
    );
    MOCK_METHOD(void, moveToMinLimitSwitch, (), (override));
    MOCK_METHOD(void, moveToMaxLimitSwitch, (), (override));
    MOCK_METHOD(void, homeAxis, (), (override));

    MOCK_METHOD(
        bool,
        isAtPositionInMicrometers,
        (uint32_t value),
        (const override)
    );

    MOCK_METHOD(
        bool,
        isAtPositionInSteps,
        (uint32_t value),
        (const override)
    );

    MOCK_METHOD(
        uint32_t,
        getCurrentPositionInMicrometers,
        (),
        (const override)
    );

    MOCK_METHOD(bool, isAtMinLimit, (), (const override));
    MOCK_METHOD(bool, isAtMaxLimit, (), (const override));

    MOCK_METHOD(void, cancelMovement, (), (override));
};
}