#pragma once

#include "application/System/Ports/IGpioPin.hpp"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

using namespace testing;

namespace ATC {
class GpioPinMock : public IGpioPin {
public:
    MOCK_METHOD(void, init, (GpioMode, GpioPull), (override));

    MOCK_METHOD(void, setHigh, (), (override));

    MOCK_METHOD(void, setLow, (), (override));

    MOCK_METHOD(void, toggle, (), (override));

    MOCK_METHOD(bool, isHigh, (), (const override));

    MOCK_METHOD(bool, isLow, (), (const override));
};
}