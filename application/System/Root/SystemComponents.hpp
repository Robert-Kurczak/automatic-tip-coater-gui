#pragma once

#include "application/System/Controllers/AxisController/XAxisController/IXAxisController.hpp"
#include "application/System/Controllers/AxisController/YAxisController/IYAxisController.hpp"
#include "application/System/Controllers/AxisController/ZAxisController/IZAxisController.hpp"
#include "application/System/Controllers/HeaterController/IHeaterController.hpp"
#include "application/System/Controllers/PersistentStorageController/IPersistentStorageController.hpp"
#include "application/System/Controllers/SpindleController/ISpindleController.hpp"
#include "application/System/Controllers/TouchPanelController/ITouchPanelController.hpp"
#include "application/System/Drivers/Display/IDisplay.hpp"
#include "application/System/Tasks/TaskScheduler/ITaskScheduler.hpp"

namespace ATC {
struct SystemComponents {
    IPersistentStorageController& persistentStorageController;
    IXAxisController& xAxisController;
    IYAxisController& yAxisController;
    IZAxisController& zAxisController;
    ISpindleController& spindleController;
    IHeaterController& heaterController;
    IDisplay& display;
    ITouchPanelController& touchPanelController;
    ITaskScheduler& taskScheduler;
};
}