#pragma once

#include "application/Utils/Math.hpp"

namespace ATC {
class ITouchPanelController {
public:
    ITouchPanelController() = default;
    ITouchPanelController(const ITouchPanelController&) = delete;
    ITouchPanelController& operator=(const ITouchPanelController&) =
        delete;
    ITouchPanelController(ITouchPanelController&&) = delete;
    ITouchPanelController& operator=(ITouchPanelController&&) = delete;

    virtual ~ITouchPanelController() = default;

    virtual void init() = 0;

    virtual Vector2 readPosition() = 0;
};
}
