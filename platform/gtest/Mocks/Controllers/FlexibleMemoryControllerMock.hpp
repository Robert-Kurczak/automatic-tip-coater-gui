#pragma once

#include "application/System/Drivers/FlexibleMemoryController/IFlexibleMemoryController.hpp"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

using namespace testing;

namespace ATC {
class FlexibleMemoryControllerMock : public IFlexibleMemoryController {
public:
    MOCK_METHOD(void, writeRegister, (RegisterNumber), (override));

    MOCK_METHOD(void, writeData, (Data), (override));

    MOCK_METHOD(void, write, (const Instruction&), (override));

    MOCK_METHOD(uint16_t, readData, (), (const override));

    MOCK_METHOD(uint16_t, read, (RegisterNumber), (const override));
};
};