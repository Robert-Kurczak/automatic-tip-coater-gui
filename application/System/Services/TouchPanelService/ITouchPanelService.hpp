#pragma once

#include "application/Utils/Math.hpp"

namespace ATC {
class ITouchPanelService {
public:
    virtual ~ITouchPanelService() = default;

    virtual Vector2 readPosition() = 0;
};
}