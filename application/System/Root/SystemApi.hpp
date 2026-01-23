#pragma once

#include "application/System/Controllers/AxisMotionController/IAxisMotionController.hpp"
#include "application/System/Services/AxisConfiguratorService/IAxisConfiguratorService.hpp"
#include "application/System/Services/AxisInterruptService/IAxisInterruptService.hpp"
#include "application/System/Services/ConsumableTaskService/IConsumableTaskService.hpp"
#include "application/System/Services/DisplayService/IDisplayService.hpp"
#include "application/System/Services/HeaterConfiguratorService/IHeaterConfiguratorService.hpp"
#include "application/System/Services/SpindleConfiguratorService/ISpindleConfiguratorService.hpp"
#include "application/System/Services/TaskControlService/ITaskControlService.hpp"
#include "application/System/Services/TouchPanelService/ITouchPanelService.hpp"
#include "application/System/Tasks/Task/AxisTestTask/AxisTestResults.hpp"
#include "application/System/Tasks/Task/HeaterTestTask/HeaterTestResults.hpp"
#include "application/System/Tasks/Task/SpindleTestTask/SpindleTestResults.hpp"

namespace ATC {
struct SystemPeripherals {
    // NOLINTBEGIN(cppcoreguidelines-avoid-const-or-ref-data-members)
    IDisplayService& display;
    ITouchPanelService& touchPanel;
    // NOLINTEND(cppcoreguidelines-avoid-const-or-ref-data-members)
};

struct SystemInterrupts {
    // NOLINTBEGIN(cppcoreguidelines-avoid-const-or-ref-data-members)
    IAxisInterruptService& xAxisInterruptService;
    IAxisInterruptService& yAxisInterruptService;
    IAxisInterruptService& zAxisInterruptService;
    // NOLINTEND(cppcoreguidelines-avoid-const-or-ref-data-members)
};

struct SystemConfigurators {
    // NOLINTBEGIN(cppcoreguidelines-avoid-const-or-ref-data-members)
    IAxisConfiguratorService& xAxisConfigurator;
    IAxisConfiguratorService& yAxisConfigurator;
    IAxisConfiguratorService& zAxisConfigurator;
    ISpindleConfiguratorService& spindleConfigurator;
    IHeaterConfiguratorService& heaterConfigurator;
    // NOLINTEND(cppcoreguidelines-avoid-const-or-ref-data-members)
};

struct SystemTasks {
    // NOLINTBEGIN(cppcoreguidelines-avoid-const-or-ref-data-members)
    IConsumableTaskService<bool>& coatingTask;
    IConsumableTaskService<bool>& calibrationTask;
    IConsumableTaskService<AxisTestResults>& xAxisTestTask;
    IConsumableTaskService<AxisTestResults>& yAxisTestTask;
    IConsumableTaskService<AxisTestResults>& zAxisTestTask;
    IConsumableTaskService<SpindleTestResults>& spindleTestTask;
    IConsumableTaskService<HeaterTestResults>& heaterTestTask;
    ITaskControlService& taskControl;
    // NOLINTEND(cppcoreguidelines-avoid-const-or-ref-data-members)
};

struct SystemApi {
    // NOLINTBEGIN(cppcoreguidelines-avoid-const-or-ref-data-members)
    SystemInterrupts interrupts;
    SystemPeripherals peripherals;
    SystemConfigurators configurators;
    SystemTasks tasks;
    // NOLINTEND(cppcoreguidelines-avoid-const-or-ref-data-members)
};
}