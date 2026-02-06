#pragma once

#include "Adapters/Adc/Adc.hpp"
#include "Adapters/AsyncPulsePin/AsyncPulsePin.hpp"
#include "Adapters/GpioPin/GpioPin.hpp"
#include "Adapters/I2c/I2c.hpp"
#include "Adapters/PwmPin/PwmPin.hpp"
#include "Adapters/Spi/Spi.hpp"
#include "Adapters/SystemClock/SystemClock.hpp"
#include "Adapters/Uart/Uart.hpp"
#include "application/System/Config/ComponentConfig/AxisMotionConfig.hpp"
#include "application/System/Config/ComponentConfig/ConfiguratorsConfig.hpp"
#include "application/System/Config/ComponentConfig/HeaterConfig.hpp"
#include "application/System/Config/ComponentConfig/Xpt2046TouchPanelConfig.hpp"
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
#include "application/System/Drivers/MotorDriver/Drv8876MotorDriver/Drv8876MotorDriver.hpp"
#include "application/System/Drivers/OutputSwitch/GpioOutputSwitch/GpioOutputSwitch.hpp"
#include "application/System/Drivers/PersistentStorage/Eeprom24Lc64/Eeprom24Lc64.hpp"
#include "application/System/Drivers/ResistiveTouchPanel/Xpt2046TouchPanel/Xpt2046TouchPanel.hpp"
#include "application/System/Drivers/StepperDriver/Tmc2226StepperDriver/Tmc2226StepperDriver.hpp"
#include "application/System/Drivers/TemperatureSensor/Thermistor104Nt4/Thermistor104Nt4.hpp"
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
#include "stm32u5xx_hal_adc.h"
#include "stm32u5xx_hal_i2c.h"

extern SPI_HandleTypeDef hspi1;
extern I2C_HandleTypeDef hi2c1;
extern UART_HandleTypeDef huart1;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim5;
extern ADC_HandleTypeDef hadc1;
namespace ATC {
static constexpr uint32_t SPI1_BAUD_RATE_IN_KILOHERTZ = 1250;

class TargetSystemRoot : public SystemRoot {
private:
    Uart uart_ {huart1};
    Spi spi_ {hspi1, SPI1_BAUD_RATE_IN_KILOHERTZ};
    I2c i2c_ {hi2c1};

    SystemClock systemClock_ {};
    UartLoggerSink loggerSink_ {uart_};

    Eeprom24Lc64 persistentStorage_ {i2c_, 0x00};
    PersistentStorageController persistentStorageController_ {
        loggerSink_,
        persistentStorage_
    };

    AsyncPulsePin xAxisStepPin_ {htim3, TIM_CHANNEL_1};
    GpioPin xAxisDirectionPin_ {*xAxis_DIR_GPIO_Port, xAxis_DIR_Pin};
    GpioPin xAxisDiagnosticPin_ {*xAxis_DIAG_GPIO_Port, xAxis_DIAG_Pin};
    Tmc2226StepperDriverPinout xAxisStepperDriverPinout_ {
        .stepPin = xAxisStepPin_,
        .directionPin = xAxisDirectionPin_,
        .diagnosticPin = xAxisDiagnosticPin_,
    };
    Tmc2226StepperDriver xAxisStepperDriver_ {xAxisStepperDriverPinout_};
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
    Tmc2226StepperDriverPinout yAxisStepperDriverPinout_ {
        .stepPin = yAxisStepPin_,
        .directionPin = yAxisDirectionPin_,
        .diagnosticPin = yAxisDiagnosticPin_,
    };
    Tmc2226StepperDriver yAxisStepperDriver_ {yAxisStepperDriverPinout_};
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
    Tmc2226StepperDriverPinout zAxisStepperDriverPinout_ {
        .stepPin = zAxisStepPin_,
        .directionPin = zAxisDirectionPin_,
        .diagnosticPin = zAxisDiagnosticPin_
    };
    Tmc2226StepperDriver zAxisStepperDriver_ {zAxisStepperDriverPinout_};
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

    GpioPin motorDriverModePin_ {*Spindle_MD_GPIO_Port, Spindle_MD_Pin};
    PwmPin motorDriverEnablePin_ {htim3, TIM_CHANNEL_1};
    GpioPin motorDriverPhasePin_ {*Spindle_PH_GPIO_Port, Spindle_PH_Pin};
    GpioPin motorDriverSleepPin_ {
        *Spindle_SLP_GPIO_Port,
        Spindle_SLP_Pin
    };
    GpioPin motorDriverFaultPin_ {
        *Spindle_FLT_GPIO_Port,
        Spindle_FLT_Pin
    };
    Drv8876MotorDriverPinout motorDriverPinout_ {
        .modePin = motorDriverModePin_,
        .enablePin = motorDriverEnablePin_,
        .phasePin = motorDriverPhasePin_,
        .sleepPin = motorDriverSleepPin_,
        .faultPin = motorDriverFaultPin_
    };
    DRV8876MotorDriver motorDriver_ {motorDriverPinout_};
    SpindleController spindleController_ {
        loggerSink_,
        systemClock_,
        motorDriver_
    };

    GpioPin heaterTogglePin_ {*Heater_EN_GPIO_Port, Heater_EN_Pin};
    GpioOutputSwitch<ActiveLevel::ActiveHigh> heaterSwitch_ {
        heaterTogglePin_
    };
    Adc adc_ {
        hadc1,
        Adc::ResolutionBits {10},
        Adc::ReferenceVoltage {3.3f}
    };
    Thermistor104Nt4 heaterThermistor_ {loggerSink_, adc_};
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

    Xpt2046TouchPanel touchPanel_ {
        loggerSink_,
        xpt2046TouchPanelPinout_,
        spi_
    };

    ResistiveTouchPanelController touchPanelController_ {
        touchPanel_,
        systemClock_,
        XPT_2046_TOUCH_PANEL_CONFIG
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
        HEATER_CONFIGURATOR_PARAMETERS
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
