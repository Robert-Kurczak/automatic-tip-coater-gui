#pragma once

#include "application/System/Ports/IPwmPin.hpp"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

using namespace testing;

namespace ATC {
class PwmPinMock: public IPwmPin {
public:
    MOCK_METHOD(void, setDutyCycle, (uint8_t), (override));
};
}