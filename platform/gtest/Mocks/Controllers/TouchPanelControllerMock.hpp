#pragma once

#include "application/System/Controllers/TouchPanelController/ITouchPanelController.hpp"

#include "gmock/gmock.h"

using namespace testing;

namespace ATC {
class TouchPanelControllerMock : public ITouchPanelController {
public:
    MOCK_METHOD(void, init, (), (override));
    MOCK_METHOD(Vector2, readPosition, (), (override));
};
}