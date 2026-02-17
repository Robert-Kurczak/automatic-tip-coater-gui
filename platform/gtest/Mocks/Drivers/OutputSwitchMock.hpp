#pragma once

#include "application/System/Drivers/OutputSwitch/IOutputSwitch.hpp"

#include "gmock/gmock.h"
namespace ATC {
class OutputSwitchMock : public IOutputSwitch {
public:
    MOCK_METHOD(void, init, (), (override));
    MOCK_METHOD(void, turnOn, (), (override));
    MOCK_METHOD(void, turnOff, (), (override));
};
}