#pragma once

#include "application/System/Controllers/TouchPanelController/ResistiveTouchPanelController/ResistiveTouchPanelParameters.hpp"
namespace ATC {
constexpr ResistiveTouchPanelParameters XPT_2046_TOUCH_PANEL_CONFIG {
    .rawWorkingArea =
        Rectangle {
                   .xStart = 130,
                   .xEnd = 1900,
                   .yStart = 80,
                   .yEnd = 1950
        },
    .pixelResolution = Vector2 {.x = 480, .y = 800},
    .pressureTreshold = 1300,
    .invertYAxis = true
};
}