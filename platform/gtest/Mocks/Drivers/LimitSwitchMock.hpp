#pragma once

#include "application/System/Drivers/LimitSwitch/ILimitSwitch.hpp"

#include "gmock/gmock.h"

using namespace testing;

namespace ATC {
class LimitSwitchMock : public ILimitSwitch {
public:
    MOCK_METHOD(void, init, (), (override));

    MOCK_METHOD(bool, isActive, (), (const override));
};
}