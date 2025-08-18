#pragma once

#include "Adapters/GpioPin/GpioPin.hpp"
#include "Adapters/Spi/Spi.hpp"
#include "Adapters/SystemClock/SystemClock.hpp"
#include "Adapters/Uart/Uart.hpp"
#include "application/Controllers/AxisControllers/XAxisController/XAxisController.hpp"
#include "application/Controllers/AxisControllers/YAxisController/YAxisController.hpp"
#include "application/Controllers/AxisControllers/ZAxisController/ZAxisController.hpp"
#include "application/Controllers/HeaterController/HysteresisHeaterController/HysteresisHeaterController.hpp"
#include "application/Drivers/Switch/GpioActiveHighSwitch/GpioActiveHighSwitch.hpp"
#include "application/Drivers/TemperatureSensor/Thermistor/Thermistor.hpp"
#include "application/Hardware/FlexibleMemoryController/FlexibleMemoryController.hpp"
#include "application/Hardware/FramebufferDisplay/Ws17143Display/Ws17143Display.hpp"
#include "application/Hardware/Rotator/DcMotorRotator/DcMotorRotator.hpp"
#include "application/Hardware/TouchController/Xpt2046TouchController/Xpt2046TouchController.hpp"
#include "application/System/Board/Board.hpp"
#include "application/System/Board/BoardDevices.hpp"
#include "application/System/Logger/UartLogger/UartLogger.hpp"
#include "main.h"

extern SPI_HandleTypeDef hspi1;
extern UART_HandleTypeDef huart1;

namespace ATC {
class TargetBoard : public Board {
private:
    Uart uart {huart1};
    UartLogger uartLogger {uart};

    XAxisController xAxisController_ {uartLogger};
    YAxisController yAxisController_ {uartLogger};
    ZAxisController zAxisController_ {uartLogger};
    DcMotorRotator rotator_ {uartLogger};

    GpioPin heaterTogglePin_ {*Heater_EN_GPIO_Port, Heater_EN_Pin};
    GpioActiveHighSwitch heaterSwitch_ {heaterTogglePin_};
    Thermistor heaterThermistor_ {uartLogger};
    HysteresisHeaterController heaterController_ {
        uartLogger,
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
    GpioPin touchControllerChipSelectPin_ {
        *TouchPanel_CS_GPIO_Port,
        TouchPanel_CS_Pin
    };
    GpioPin touchControllerInterruptPin_ {
        *TouchPanel_IRQ_GPIO_Port,
        TouchPanel_IRQ_Pin
    };
    Xpt2046TouchControllerPinout xpt2046Pinout_ {
        .chipSelectPin_ = touchControllerChipSelectPin_,
        .touchInterruptPin_ = touchControllerInterruptPin_
    };
    Xpt2046TouchController touchController_ {
        xpt2046Pinout_,
        spi_,
        systemClock_,
        Rectangle {
                   .xStart_ = 130,
                   .xEnd_ = 1900,
                   .yStart_ = 80,
                   .yEnd_ = 1950
        },
        Vector2 {.x_ = 480, .y_ = 800}
    };

    BoardDevices targetDevices_ {
        .xAxisController = xAxisController_,
        .yAxisController = yAxisController_,
        .zAxisController = zAxisController_,
        .rotator = rotator_,
        .heaterController = heaterController_,
        .display = display_,
        .touchController = touchController_
    };

    TargetBoard();

public:
    static TargetBoard& getBoard();
};
}
