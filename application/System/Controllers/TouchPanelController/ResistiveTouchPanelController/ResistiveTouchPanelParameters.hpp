#pragma once

#include "application/Utils/Math.hpp"

namespace ATC {
struct ResistiveTouchPanelParameters {
    Rectangle rawWorkingArea;
    Vector2 pixelResolution;
    uint16_t pressureTreshold;
    bool invertYAxis;
};
}