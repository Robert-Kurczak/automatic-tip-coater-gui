#pragma once

#include "ITouchPanelService.hpp"
#include "application/System/Controllers/TouchPanelController/ITouchPanelController.hpp"

namespace ATC {
class TouchPanelService : public ITouchPanelService {
private:
    ITouchPanelController& touchPanelController_;

public:
    TouchPanelService(ITouchPanelController& touchPanelController);

    virtual Vector2 readPosition() override;
};
}