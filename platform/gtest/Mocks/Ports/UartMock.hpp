#pragma once

#include "application/System/Ports/IUart.hpp"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

using namespace testing;

namespace ATC {
class UartMock : public IUart {
public:
    MOCK_METHOD(void, write, (const std::span<const char>&), (override));

    MOCK_METHOD(void, read, (const std::span<char>&), (override));
};
}