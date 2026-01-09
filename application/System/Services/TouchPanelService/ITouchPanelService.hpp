#pragma once

#include "application/Utils/Math.hpp"

namespace ATC {
class ITouchPanelService {
public:
    ITouchPanelService() = default;
    ITouchPanelService(const ITouchPanelService&) = delete;
    ITouchPanelService& operator=(const ITouchPanelService&) = delete;
    ITouchPanelService(ITouchPanelService&&) = delete;
    ITouchPanelService& operator=(ITouchPanelService&&) = delete;
    virtual ~ITouchPanelService() = default;

    [[nodiscard]] virtual Vector2 readPosition() = 0;
};
}