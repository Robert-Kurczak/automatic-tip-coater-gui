#pragma once

#include "application/Controllers/AxisControllers/XAxisController/IXAxisController.hpp"
#include "application/Controllers/AxisControllers/YAxisController/IYAxisController.hpp"
#include "application/Controllers/AxisControllers/ZAxisController/IZAxisController.hpp"
#include "application/Controllers/HeaterController/IHeaterController.hpp"
#include "application/Controllers/SpindleController/ISpindleController.hpp"
#include "application/Controllers/TouchPanelController/ITouchPanelController.hpp"
#include "application/Drivers/FramebufferDisplay/IFramebufferDisplay.hpp"

namespace ATC {
struct BoardDevices {
    IXAxisController& xAxisController;
    IYAxisController& yAxisController;
    IZAxisController& zAxisController;
    ISpindleController& spindleController;
    IHeaterController& heaterController;
    IFramebufferDisplay& display;
    ITouchPanelController& touchPanelController;
};
}