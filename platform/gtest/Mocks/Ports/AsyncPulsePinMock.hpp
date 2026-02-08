#pragma once

#include "application/System/Ports/IAsyncPulsePin.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace testing;

namespace ATC {
class AsyncPulsePinMock : public IAsyncPulsePin {
public:
    MOCK_METHOD(void, init, (), (override));

    MOCK_METHOD(void, enable, (), (override));

    MOCK_METHOD(void, disable, (), (override));

    MOCK_METHOD(
        void,
        setToggleMicroseconds,
        (uint32_t value),
        (override)
    );
};
}