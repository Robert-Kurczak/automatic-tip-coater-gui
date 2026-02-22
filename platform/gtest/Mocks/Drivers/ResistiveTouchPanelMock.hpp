#pragma once

#include "application/System/Drivers/ResistiveTouchPanel/IResistiveTouchPanel.hpp"

#include "gmock/gmock.h"

namespace ATC {
class ResistiveTouchPanelMock : public IResistiveTouchPanel {
public:
    MOCK_METHOD(void, init, (), (override));
    MOCK_METHOD(bool, isTouchDetected, (), (override));
    MOCK_METHOD(uint16_t, readRawX, (), (override));
    MOCK_METHOD(uint16_t, readRawY, (), (override));
    MOCK_METHOD(uint16_t, readRawZ, (), (override));
};
}