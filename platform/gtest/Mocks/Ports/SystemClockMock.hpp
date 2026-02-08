#pragma once

#include "application/System/Ports/ISystemClock.hpp"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

using namespace testing;

namespace ATC {
class SystemClockMock : public ISystemClock {
public:
    MOCK_METHOD(void, delayMilliseconds, (uint32_t value), (override));

    MOCK_METHOD(uint32_t, getMillisecondsSinceStart, (), (override));
};
}