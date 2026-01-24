#pragma once

#include "Adapters/AsyncPulsePin/AsyncPulsePin.hpp"
#include "Adapters/GpioPin/GpioPin.hpp"
#include "Adapters/PwmPin/PwmPin.hpp"
#include "Adapters/Spi/Spi.hpp"
#include "Adapters/SystemClock/SystemClock.hpp"
#include "Adapters/Uart/Uart.hpp"
#include "application/System/Config/ComponentConfig/AxisMotionConfig.hpp"
#include "application/System/Config/ComponentConfig/ConfiguratorsConfig.hpp"
#include "application/System/Config/ComponentConfig/HeaterConfig.hpp"
#include "application/System/Controllers/AxisController/XAxisController/XAxisController.hpp"
#include "application/System/Controllers/AxisController/YAxisController/YAxisController.hpp"
#include "application/System/Controllers/AxisController/ZAxisController/ZAxisController.hpp"
#include "application/System/Controllers/AxisMotionController/AxisMotionController.hpp"
#include "application/System/Controllers/HeaterController/HysteresisHeaterController/HysteresisHeaterController.hpp"
#include "application/System/Controllers/PersistentStorageController/PersistentStorageController.hpp"
#include "application/System/Controllers/SpindleController/SpindleController.hpp"
#include "application/System/Controllers/TouchPanelController/ResistiveTouchPanelController/ResistiveTouchPanelController.hpp"
#include "application/System/Drivers/Display/Ws17143Display/Ws17143Display.hpp"
#include "application/System/Drivers/FlexibleMemoryController/FlexibleMemoryController.hpp"
#include "application/System/Drivers/LimitSwitch/GpioLimitSwitch/GpioLimitSwitch.hpp"
#include "application/System/Drivers/LoggerSink/UartLoggerSink/UartLoggerSink.hpp"
#include "application/System/Drivers/Motor/PwmDcMotor/PwmDcMotor.hpp"
#include "application/System/Drivers/OutputSwitch/GpioOutputSwitch/GpioOutputSwitch.hpp"
#include "application/System/Drivers/PersistentStorage/Eeprom/Eeprom.hpp"
#include "application/System/Drivers/ResistiveTouchPanel/Xpt2046TouchPanel/Xpt2046TouchPanel.hpp"
#include "application/System/Drivers/StepperDriver/Tmc2310StepperDriver/Tmc2310StepperDriver.hpp"
#include "application/System/Drivers/TemperatureSensor/Thermistor/Thermistor.hpp"
#include "application/System/Root/SystemApi.hpp"
#include "application/System/Root/SystemRoot.hpp"
#include "application/System/Services/AxisConfiguratorService/XAxisConfiguratorService/XAxisConfiguratorService.hpp"
#include "application/System/Services/AxisConfiguratorService/YAxisConfiguratorService/YAxisConfiguratorService.hpp"
#include "application/System/Services/AxisConfiguratorService/ZAxisConfiguratorService/ZAxisConfiguratorService.hpp"
#include "application/System/Services/AxisInterruptService/AxisInterruptService.hpp"
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
#include "main.h"

extern SPI_HandleTypeDef hspi1;
extern UART_HandleTypeDef huart1;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim5;
namespace ATC {
class TargetSystemRoot : public SystemRoot {
private:
    SystemClock systemClock_ {};
    Uart uart_ {huart1};
    UartLoggerSink loggerSink_ {uart_};

    Eeprom eeprom_ {loggerSink_};
    PersistentStorageController persistentStorageController_ {
        loggerSink_,
        eeprom_
    };

    AsyncPulsePin xAxisStepPin_ {htim3, TIM_CHANNEL_1};
    GpioPin xAxisDirectionPin_ {*xAxis_DIR_GPIO_Port, xAxis_DIR_Pin};
    GpioPin xAxisDiagnosticPin_ {*xAxis_DIAG_GPIO_Port, xAxis_DIAG_Pin};
    GpioPin xAxisChipSelectPin_ {*xAxis_CS_GPIO_Port, xAxis_CS_Pin};
    Tmc2310StepperDriverPinout xAxisStepperDriverPinout_ {
        .stepPin = xAxisStepPin_,
        .directionPin = xAxisDirectionPin_,
        .diagnosticPin = xAxisDiagnosticPin_,
        .chipSelectPin = xAxisChipSelectPin_
    };
    Tmc2310StepperDriver xAxisStepperDriver_ {
        xAxisStepperDriverPinout_,
        spi_
    };
    GpioPin xAxisMinLimitSwitchPin_ {
        *xAxis_MIN_LIMIT_GPIO_Port,
        xAxis_MIN_LIMIT_Pin
    };
    GpioLimitSwitch<ActiveLevel::ActiveLow> xAxisMinLimitSwitch_ {
        xAxisMinLimitSwitchPin_
    };
    GpioPin xAxisMaxLimitSwitchPin_ {
        *xAxis_MAX_LIMIT_GPIO_Port,
        xAxis_MAX_LIMIT_Pin
    };
    GpioLimitSwitch<ActiveLevel::ActiveLow> xAxisMaxLimitSwitch_ {
        xAxisMaxLimitSwitchPin_
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

    AsyncPulsePin yAxisStepPin_ {htim4, TIM_CHANNEL_1};
    GpioPin yAxisDirectionPin_ {*yAxis_DIR_GPIO_Port, yAxis_DIR_Pin};
    GpioPin yAxisDiagnosticPin_ {*yAxis_DIAG_GPIO_Port, yAxis_DIAG_Pin};
    GpioPin yAxisChipSelectPin_ {*yAxis_CS_GPIO_Port, yAxis_CS_Pin};
    Tmc2310StepperDriverPinout yAxisStepperDriverPinout_ {
        .stepPin = yAxisStepPin_,
        .directionPin = yAxisDirectionPin_,
        .diagnosticPin = yAxisDiagnosticPin_,
        .chipSelectPin = yAxisChipSelectPin_
    };
    Tmc2310StepperDriver yAxisStepperDriver_ {
        yAxisStepperDriverPinout_,
        spi_
    };
    GpioPin yAxisMinLimitSwitchPin_ {
        *yAxis_MIN_LIMIT_GPIO_Port,
        yAxis_MIN_LIMIT_Pin
    };
    GpioLimitSwitch<ActiveLevel::ActiveLow> yAxisMinLimitSwitch_ {
        yAxisMinLimitSwitchPin_
    };
    GpioPin yAxisMaxLimitSwitchPin_ {
        *yAxis_MAX_LIMIT_GPIO_Port,
        yAxis_MAX_LIMIT_Pin
    };
    GpioLimitSwitch<ActiveLevel::ActiveLow> yAxisMaxLimitSwitch_ {
        yAxisMaxLimitSwitchPin_
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
    GpioPin tipLimitSwitchPin_ {*tip_LIMIT_GPIO_Port, tip_LIMIT_Pin};
    GpioLimitSwitch<ActiveLevel::ActiveLow> tipLimitSwitch_ {
        tipLimitSwitchPin_
    };
    YAxisController yAxisController_ {
        loggerSink_,
        yAxisMotionController_,
        tipLimitSwitch_
    };

    AsyncPulsePin zAxisStepPin_ {htim5, TIM_CHANNEL_1};
    GpioPin zAxisDirectionPin_ {*zAxis_DIR_GPIO_Port, zAxis_DIR_Pin};
    GpioPin zAxisDiagnosticPin_ {*zAxis_DIAG_GPIO_Port, zAxis_DIAG_Pin};
    GpioPin zAxisChipSelectPin_ {*zAxis_CS_GPIO_Port, zAxis_CS_Pin};
    Tmc2310StepperDriverPinout zAxisStepperDriverPinout_ {
        .stepPin = zAxisStepPin_,
        .directionPin = zAxisDirectionPin_,
        .diagnosticPin = zAxisDiagnosticPin_,
        .chipSelectPin = zAxisChipSelectPin_
    };
    Tmc2310StepperDriver zAxisStepperDriver_ {
        zAxisStepperDriverPinout_,
        spi_
    };
    GpioPin zAxisMinLimitSwitchPin_ {
        *zAxis_MIN_LIMIT_GPIO_Port,
        zAxis_MIN_LIMIT_Pin
    };
    GpioLimitSwitch<ActiveLevel::ActiveLow> zAxisMinLimitSwitch_ {
        zAxisMinLimitSwitchPin_
    };
    GpioPin zAxisMaxLimitSwitchPin_ {
        *zAxis_MAX_LIMIT_GPIO_Port,
        zAxis_MAX_LIMIT_Pin
    };
    GpioLimitSwitch<ActiveLevel::ActiveLow> zAxisMaxLimitSwitch_ {
        zAxisMaxLimitSwitchPin_
    };
    LimitSwitchPair zAxisLimitSwitchPair_ {
        .minLimitSwitch = zAxisMinLimitSwitch_,
        .maxLimitSwitch = zAxisMaxLimitSwitch_
    };
    AxisMotionController zAxisMotionController_ {
        loggerSink_,
        zAxisStepperDriver_,
        zAxisLimitSwitchPair_,
        Z_AXIS_MOTION_PARAMETERS
    };
    ZAxisController zAxisController_ {
        loggerSink_,
        zAxisMotionController_
    };

    PwmPin dcMotorPwmPin_ {htim3, TIM_CHANNEL_1};
    GpioPin dcMotorDirectionPin_ {
        *Spindle_DIR_GPIO_Port,
        Spindle_DIR_Pin
    };
    GpioPin dcMotorFaultPin_ {
        *Spindle_FAULT_GPIO_Port,
        Spindle_FAULT_Pin
    };
    PwmDcMotorPinout pwmDcMotorPinout_ {
        .speedPwmPin = dcMotorPwmPin_,
        .directionPin = dcMotorDirectionPin_,
        .faultPin = dcMotorFaultPin_
    };
    PwmDcMotor pwmDcMotor_ {pwmDcMotorPinout_};
    SpindleController spindleController_ {
        loggerSink_,
        systemClock_,
        pwmDcMotor_
    };

    GpioPin heaterTogglePin_ {*Heater_EN_GPIO_Port, Heater_EN_Pin};
    GpioOutputSwitch<ActiveLevel::ActiveHigh> heaterSwitch_ {
        heaterTogglePin_
    };
    Thermistor heaterThermistor_ {loggerSink_};
    HysteresisHeaterController heaterController_ {
        loggerSink_,
        heaterSwitch_,
        heaterThermistor_,
        HEATER_HYSTERESIS_MARGIN_IN_CELSIUS
    };

    FlexibleMemoryController flexibleMemoryController_ {
        IFlexibleMemoryController::RegisterAddress {0x60000000},
        IFlexibleMemoryController::DataAddress {0x60000002}
    };
    GpioPin lcdResetPin_ {*LCD_RS_GPIO_Port, LCD_RS_Pin};
    Ws17143DisplayPinout pinout_ {.lcdResetPin_ = lcdResetPin_};
    Ws17143Display display_ {
        pinout_,
        flexibleMemoryController_,
        systemClock_
    };

    Spi spi_ {hspi1};
    GpioPin touchPanelChipSelectPin_ {
        *TouchPanel_CS_GPIO_Port,
        TouchPanel_CS_Pin
    };
    GpioPin touchPanelInterruptPin_ {
        *TouchPanel_IRQ_GPIO_Port,
        TouchPanel_IRQ_Pin
    };
    Xpt2046TouchPanelPinout xpt2046TouchPanelPinout_ {
        .chipSelectPin = touchPanelChipSelectPin_,
        .touchInterruptPin = touchPanelInterruptPin_
    };

    Xpt2046TouchPanel touchPanel_ {xpt2046TouchPanelPinout_, spi_};

    ResistiveTouchPanelController touchPanelController_ {
        touchPanel_,
        systemClock_,
        Rectangle {
                   .xStart = 130,
                   .xEnd = 1900,
                   .yStart = 80,
                   .yEnd = 1950
        },
        Vector2 {.x = 480, .y = 800},
        1300,
        true
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

    AxisInterruptService xAxisInterruptService_ {xAxisMotionController_};
    AxisInterruptService yAxisInterruptService_ {xAxisMotionController_};
    AxisInterruptService zAxisInterruptService_ {xAxisMotionController_};

    SystemInterrupts systemInterrupts_ {
        .xAxisInterruptService = xAxisInterruptService_,
        .yAxisInterruptService = yAxisInterruptService_,
        .zAxisInterruptService = zAxisInterruptService_
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
        .interrupts = systemInterrupts_,
        .peripherals = systemPeripherals_,
        .configurators = systemConfigurators_,
        .tasks = systemTasks_
    };

    TargetSystemRoot();

public:
    static TargetSystemRoot& getSystemRoot();
};
}
