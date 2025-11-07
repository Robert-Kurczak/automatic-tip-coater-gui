#pragma once

#include "Adapters/GpioPin/GpioPin.hpp"
#include "Adapters/PwmPin/PwmPin.hpp"
#include "Adapters/Spi/Spi.hpp"
#include "Adapters/SystemClock/SystemClock.hpp"
#include "Adapters/Uart/Uart.hpp"
#include "application/System/Controllers/AxisController/XAxisController/XAxisController.hpp"
#include "application/System/Controllers/AxisController/YAxisController/YAxisController.hpp"
#include "application/System/Controllers/AxisController/ZAxisController/ZAxisController.hpp"
#include "application/System/Controllers/HeaterController/HysteresisHeaterController/HysteresisHeaterController.hpp"
#include "application/System/Controllers/PersistentStorageController/PersistentStorageController.hpp"
#include "application/System/Controllers/SpindleController/SpindleController.hpp"
#include "application/System/Controllers/TouchPanelController/ResistiveTouchPanelController/ResistiveTouchPanelController.hpp"
#include "application/System/Drivers/Display/Ws17143Display/Ws17143Display.hpp"
#include "application/System/Drivers/FlexibleMemoryController/FlexibleMemoryController.hpp"
#include "application/System/Drivers/LoggerSink/UartLoggerSink/UartLoggerSink.hpp"
#include "application/System/Drivers/Motor/PwmDcMotor/PwmDcMotor.hpp"
#include "application/System/Drivers/PersistentStorage/Eeprom/Eeprom.hpp"
#include "application/System/Drivers/ResistiveTouchPanel/Xpt2046TouchPanel/Xpt2046TouchPanel.hpp"
#include "application/System/Drivers/Switch/GpioActiveHighSwitch/GpioActiveHighSwitch.hpp"
#include "application/System/Drivers/TemperatureSensor/Thermistor/Thermistor.hpp"
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
#include "main.h"

extern SPI_HandleTypeDef hspi1;
extern UART_HandleTypeDef huart1;
extern TIM_HandleTypeDef htim3;

namespace ATC {
class TargetSystemRoot : public SystemRoot {
private:
    Uart uart_ {huart1};
    UartLoggerSink loggerSink_ {uart_};

    Eeprom eeprom_ {loggerSink_};
    PersistentStorageController persistentStorageController_ {loggerSink_, eeprom_};

    XAxisController xAxisController_ {loggerSink_};
    YAxisController yAxisController_ {loggerSink_};
    ZAxisController zAxisController_ {loggerSink_};

    PwmPin dcMotorPwmPin_ {htim3, TIM_CHANNEL_1};
    GpioPin dcMotorDirectionPin_ {
        *Spindle_DIR_GPIO_Port,
        Spindle_DIR_Pin
    };
    PwmDcMotorPinout pwmDcMotorPinout_ {
        .speedPwmPin = dcMotorPwmPin_,
        .directionPin = dcMotorDirectionPin_
    };
    PwmDcMotor pwmDcMotor_ {pwmDcMotorPinout_};
    SpindleController spindleController_ {loggerSink_, pwmDcMotor_};

    GpioPin heaterTogglePin_ {*Heater_EN_GPIO_Port, Heater_EN_Pin};
    GpioActiveHighSwitch heaterSwitch_ {heaterTogglePin_};
    Thermistor heaterThermistor_ {loggerSink_};
    HysteresisHeaterController heaterController_ {
        loggerSink_,
        heaterSwitch_,
        heaterThermistor_
    };

    FlexibleMemoryController flexibleMemoryController_ {
        0x60000000,
        0x60000002
    };
    SystemClock systemClock_ {};
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
                   .xStart_ = 130,
                   .xEnd_ = 1900,
                   .yStart_ = 80,
                   .yEnd_ = 1950
        },
        Vector2 {.x_ = 480, .y_ = 800},
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

    DisplayService displayService_ {display_};
    TouchPanelService touchPanelService_ {touchPanelController_};
    SystemPeripherals systemPeripherals_ {
        .display = displayService_,
        .touchPanel = touchPanelService_
    };

    XAxisConfiguratorService xAxisConfiguratorService_ {
        persistentStorageController_,
        xAxisController_,
        100,
        5,
        1000
    };
    YAxisConfiguratorService yAxisConfiguratorService_ {
        persistentStorageController_,
        yAxisController_,
        100,
        5,
        1000
    };
    ZAxisConfiguratorService zAxisConfiguratorService_ {
        persistentStorageController_,
        zAxisController_,
        100,
        5,
        1000
    };
    SpindleConfiguratorService spindleConfiguratorService_ {
        persistentStorageController_,
        spindleController_,
        3000,
        1,
        500
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
