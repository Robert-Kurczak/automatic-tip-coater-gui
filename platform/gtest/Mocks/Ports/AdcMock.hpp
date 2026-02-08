#pragma once

#include "application/System/Ports/IAdc.hpp"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

using namespace testing;

namespace ATC {
class AdcMock : public IAdc {
public:
    MOCK_METHOD(void, init, (), (const override));

    MOCK_METHOD(float, getReferenceVoltage, (), (const override));

    MOCK_METHOD(uint32_t, readRaw, (), (override));
};
}