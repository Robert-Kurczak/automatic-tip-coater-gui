#pragma once

#include "application/Controllers/AxisControllers/XAxisController/IXAxisController.hpp"
#include "application/Controllers/AxisControllers/YAxisController/IYAxisController.hpp"
#include "application/Controllers/AxisControllers/ZAxisController/IZAxisController.hpp"
#include "application/Controllers/HeaterController/IHeaterController.hpp"
#include "application/Hardware/FramebufferDisplay/IFramebufferDisplay.hpp"
#include "application/Hardware/Rotator/IRotator.hpp"
#include "application/Hardware/TouchController/ITouchController.hpp"

namespace ATC {
struct BoardDevices {
    IXAxisController& xAxisController;
    IYAxisController& yAxisController;
    IZAxisController& zAxisController;
    IRotator& rotator;
    IHeaterController& heaterController;
    IFramebufferDisplay& display;
    ITouchController& touchController;
};
}