#pragma once

#include "application/System/Services/AxisConfiguratorService/IAxisConfiguratorService.hpp"
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
    IDisplayService& display;
    ITouchPanelService& touchPanel;
};

struct SystemConfigurators {
    IAxisConfiguratorService& xAxisConfigurator;
    IAxisConfiguratorService& yAxisConfigurator;
    IAxisConfiguratorService& zAxisConfigurator;
    ISpindleConfiguratorService& spindleConfigurator;
    IHeaterConfiguratorService& heaterConfigurator;
};

struct SystemTasks {
    IConsumableTaskService<bool>& coatingTask;
    IConsumableTaskService<bool>& calibrationTask;
    IConsumableTaskService<AxisTestResults>& xAxisTestTask;
    IConsumableTaskService<AxisTestResults>& yAxisTestTask;
    IConsumableTaskService<AxisTestResults>& zAxisTestTask;
    IConsumableTaskService<SpindleTestResults>& spindleTestTask;
    IConsumableTaskService<HeaterTestResults>& heaterTestTask;
    ITaskControlService& taskControl;
};

struct SystemApi {
    SystemPeripherals peripherals;
    SystemConfigurators configurators;
    SystemTasks tasks;
};
}