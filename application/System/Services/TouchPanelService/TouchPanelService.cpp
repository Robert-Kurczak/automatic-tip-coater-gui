#include "TouchPanelService.hpp"

namespace ATC {
TouchPanelService::TouchPanelService(
    ITouchPanelController& touchPanelController
) :
    touchPanelController_(touchPanelController) {}

Vector2 TouchPanelService::readPosition() {
    return touchPanelController_.readPosition();
}
}