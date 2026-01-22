#pragma once

#include "FakeDrivers/FakeDisplay/FakeDisplay.hpp"
#include "FakeDrivers/FakeLimitSwitch/FakeLimitSwitch.hpp"
#include "FakeDrivers/FakeLoggerSink/FakeLoggerSink.hpp"
#include "FakeDrivers/FakeMotor/FakeMotor.hpp"
#include "FakeDrivers/FakePersistentStorage/FakePersistentStorage.hpp"
#include "FakeDrivers/FakeResistiveTouchPanel/FakeResistiveTouchPanel.hpp"
#include "FakeDrivers/FakeStepperDriver/FakeStepperDriver.hpp"
#include "FakeDrivers/FakeSwitch/FakeSwitch.hpp"
#include "FakeDrivers/FakeTemperatureSensor/FakeTemperatureSensor.hpp"
#include "FakePorts/FakeSystemClock/FakeSystemClock.hpp"
#include "application/System/Config/AxisMotionConfig.hpp"
#include "application/System/Config/ConfiguratorsConfig.hpp"
#include "application/System/Controllers/AxisController/XAxisController/XAxisController.hpp"
#include "application/System/Controllers/AxisController/YAxisController/YAxisController.hpp"
#include "application/System/Controllers/AxisController/ZAxisController/ZAxisController.hpp"
#include "application/System/Controllers/AxisMotionController/AxisMotionController.hpp"
#include "application/System/Controllers/HeaterController/HysteresisHeaterController/HysteresisHeaterController.hpp"
#include "application/System/Controllers/PersistentStorageController/PersistentStorageController.hpp"
#include "application/System/Controllers/SpindleController/SpindleController.hpp"
#include "application/System/Controllers/TouchPanelController/ResistiveTouchPanelController/ResistiveTouchPanelController.hpp"
#include "application/System/Drivers/StepperDriver/Tmc2301StepperDriver/Tmc2301StepperDriver.hpp"
#include "application/System/Root/SystemRoot.hpp"
#include "application/System/Services/AxisConfiguratorService/XAxisConfiguratorService/XAxisConfiguratorService.hpp"
#include "application/System/Services/AxisConfiguratorService/YAxisConfiguratorService/YAxisConfiguratorService.hpp"
#include "application/System/Services/AxisConfiguratorService/ZAxisConfiguratorService/ZAxisConfiguratorService.hpp"
#include "application/System/Services/ConsumableTaskService/ConsumableTaskService.hpp"
#include "application/System/Services/DisplayService/DisplayService.hpp"
#include "application/System/Services/HeaterConfiguratorService/HeaterConfiguratorService.hpp"
#include "application/System/Services/SpindleConfiguratorService/SpindleConfiguratorService.hpp"
#include "application/System/Services/TaskControlService/TaskControlService.hpp"
#include "application/System/Services/TouchPanelService/TouchPanelService.hpp"
#include "application/System/Tasks/Task/AxisTestTask/AxisTestTask.hpp"
#include "application/System/Tasks/Task/CalibrationTask/CalibrationTask.hpp"
#include "application/System/Tasks/Task/CoatingTask/CoatingTask.hpp"
#include "application/System/Tasks/Task/HeaterTestTask/HeaterTestTask.hpp"
#include "application/System/Tasks/Task/NullTask/NullTask.hpp"
#include "application/System/Tasks/Task/SpindleTestTask/SpindleTestTask.hpp"
#include "application/System/Tasks/TaskScheduler/SingleTaskScheduler/SingleTaskScheduler.hpp"
#include "application/Utils/Math.hpp"

namespace ATC {
class TargetSystemRoot : public SystemRoot {
private:
    FakeSystemClock systemClock_ {};
    FakeLoggerSink loggerSink_ {};

    FakePersistentStorage persistentStorage_ {
        loggerSink_,
        "atc-storage.bin",
        4096
    };
    PersistentStorageController persistentStorageController_ {
        loggerSink_,
        persistentStorage_
    };

    FakeStepperDriver xAxisStepperDriver_ {loggerSink_, "X Axis Driver"};
    FakeLimitSwitch xAxisMinLimitSwitch_ {
        loggerSink_,
        "X Axis Min Limiter"
    };
    FakeLimitSwitch xAxisMaxLimitSwitch_ {
        loggerSink_,
        "X Axis Max Limiter"
    };
    LimitSwitchPair xAxisLimitSwitchPair_ {
        .minLimitSwitch = xAxisMinLimitSwitch_,
        .maxLimitSwitch = xAxisMaxLimitSwitch_
    };
    AxisMotionController xAxisMotionController_ {
        loggerSink_,
        xAxisStepperDriver_,
        xAxisLimitSwitchPair_,
        X_AXIS_MOTION_PARAMETERS
    };

    XAxisController xAxisController_ {
        loggerSink_,
        xAxisMotionController_
    };

    FakeStepperDriver yAxisStepperDriver_ {loggerSink_, "Y Axis Driver"};
    FakeLimitSwitch yAxisMinLimitSwitch_ {
        loggerSink_,
        "Y Axis Min Limiter"
    };
    FakeLimitSwitch yAxisMaxLimitSwitch_ {
        loggerSink_,
        "Y Axis Max Limiter"
    };
    LimitSwitchPair yAxisLimitSwitchPair_ {
        .minLimitSwitch = yAxisMinLimitSwitch_,
        .maxLimitSwitch = yAxisMaxLimitSwitch_
    };
    AxisMotionController yAxisMotionController_ {
        loggerSink_,
        yAxisStepperDriver_,
        yAxisLimitSwitchPair_,
        Y_AXIS_MOTION_PARAMETERS
    };

    FakeLimitSwitch tipLimitSwitch_ {loggerSink_, "Tip Limit Switch"};

    YAxisController yAxisController_ {
        loggerSink_,
        yAxisMotionController_,
        tipLimitSwitch_
    };

    ZAxisController zAxisController_ {loggerSink_};

    FakeMotor spindleMotor_ {loggerSink_, "Spindle Motor"};
    SpindleController spindleController_ {
        loggerSink_,
        systemClock_,
        spindleMotor_
    };

    FakeSwitch fakeSwitch_ {loggerSink_, "Heater switch"};
    FakeTemperatureSensor temperatureSensor_ {
        loggerSink_,
        "TemperatureSensor"
    };
    HysteresisHeaterController heaterController_ {
        loggerSink_,
        fakeSwitch_,
        temperatureSensor_
    };

    FakeDisplay display_ {loggerSink_};

    FakeResistiveTouchPanel resistiveTouchPanel_ {loggerSink_};
    ResistiveTouchPanelController touchPanelController_ {
        resistiveTouchPanel_,
        systemClock_,
        ATC::Rectangle {
                        .xStart = 0,
                        .xEnd = 800,
                        .yStart = 0,
                        .yEnd = 480
        },
        ATC::Vector2 {.x = 800, .y = 480},
        3000
    };

    NullTask nullTask_ {};
    SingleTaskScheduler taskScheduler_ {nullTask_};

    SystemComponents targetComponents_ {
        .persistentStorageController = persistentStorageController_,
        .xAxisController = xAxisController_,
        .yAxisController = yAxisController_,
        .zAxisController = zAxisController_,
        .spindleController = spindleController_,
        .heaterController = heaterController_,
        .display = display_,
        .touchPanelController = touchPanelController_,
        .taskScheduler = taskScheduler_
    };

    DisplayService displayService_ {display_};
    TouchPanelService touchPanelService_ {touchPanelController_};
    SystemPeripherals systemPeripherals_ {
        .display = displayService_,
        .touchPanel = touchPanelService_
    };

    XAxisConfiguratorService xAxisConfiguratorService_ {
        persistentStorageController_,
        xAxisController_,
        X_AXIS_CONFIGURATOR_PARAMETERS
    };
    YAxisConfiguratorService yAxisConfiguratorService_ {
        persistentStorageController_,
        yAxisController_,
        Y_AXIS_CONFIGURATOR_PARAMETERS
    };
    ZAxisConfiguratorService zAxisConfiguratorService_ {
        persistentStorageController_,
        zAxisController_,
        Z_AXIS_CONFIGURATOR_PARAMETERS
    };
    SpindleConfiguratorService spindleConfiguratorService_ {
        persistentStorageController_,
        spindleController_,
        SPINDLE_CONFIGURATOR_PARAMETERS
    };
    HeaterConfiguratorService heaterConfiguratorService_ {
        persistentStorageController_,
        heaterController_,
        1
    };

    SystemConfigurators systemConfigurators_ {
        .xAxisConfigurator = xAxisConfiguratorService_,
        .yAxisConfigurator = yAxisConfiguratorService_,
        .zAxisConfigurator = zAxisConfiguratorService_,
        .spindleConfigurator = spindleConfiguratorService_,
        .heaterConfigurator = heaterConfiguratorService_
    };

    CalibrationTask calibrationTask_ {
        xAxisController_,
        yAxisController_,
        zAxisController_
    };
    ConsumableTaskService<bool> calibrationTaskService_ {
        taskScheduler_,
        calibrationTask_
    };

    CoatingTask coatingTask_ {
        calibrationTask_,
        xAxisController_,
        yAxisController_,
        zAxisController_,
        spindleController_,
        heaterController_
    };
    ConsumableTaskService<bool> coatingTaskService_ {
        taskScheduler_,
        coatingTask_
    };

    AxisTestTask xAxisTestTask_ {
        calibrationTask_,
        xAxisController_,
        systemClock_,
        10000
    };
    ConsumableTaskService<AxisTestResults> xAxisTestTaskService_ {
        taskScheduler_,
        xAxisTestTask_
    };

    AxisTestTask yAxisTestTask_ {
        calibrationTask_,
        yAxisController_,
        systemClock_,
        50000
    };
    ConsumableTaskService<AxisTestResults> yAxisTestTaskService_ {
        taskScheduler_,
        yAxisTestTask_
    };

    AxisTestTask zAxisTestTask_ {
        calibrationTask_,
        xAxisController_,
        systemClock_,
        30000
    };
    ConsumableTaskService<AxisTestResults> zAxisTestTaskService_ {
        taskScheduler_,
        zAxisTestTask_
    };

    SpindleTestTask spindleTestTask_ {spindleController_, 10000};
    ConsumableTaskService<SpindleTestResults> spindleTestTaskService_ {
        taskScheduler_,
        spindleTestTask_
    };

    HeaterTestTask heaterTestTask_ {
        heaterController_,
        systemClock_,
        30000
    };
    ConsumableTaskService<HeaterTestResults> heaterTestTaskService_ {
        taskScheduler_,
        heaterTestTask_
    };

    TaskControlService taskControlService_ {taskScheduler_};

    SystemTasks systemTasks_ {
        .coatingTask = coatingTaskService_,
        .calibrationTask = calibrationTaskService_,
        .xAxisTestTask = xAxisTestTaskService_,
        .yAxisTestTask = yAxisTestTaskService_,
        .zAxisTestTask = zAxisTestTaskService_,
        .spindleTestTask = spindleTestTaskService_,
        .heaterTestTask = heaterTestTaskService_,
        .taskControl = taskControlService_
    };

    SystemApi systemApi_ {
        .peripherals = systemPeripherals_,
        .configurators = systemConfigurators_,
        .tasks = systemTasks_
    };

    TargetSystemRoot();

public:
    static TargetSystemRoot& getSystemRoot();
};
}