#pragma once

#include "Adapters/DelayProvider/DelayProvider.hpp"
#include "Adapters/Uart/Uart.hpp"
#include "application/Board/Board.hpp"
#include "application/Board/BoardDevices.hpp"
#include "application/GpioPin/GpioPin.hpp"
#include "application/Hardware/Axes/XAxis/XAxis.hpp"
#include "application/Hardware/Axes/YAxis/YAxis.hpp"
#include "application/Hardware/Axes/ZAxis/ZAxis.hpp"
#include "application/Hardware/FlexibleMemoryController/FlexibleMemoryController.hpp"
#include "application/Hardware/FramebufferDisplay/Ws17143Display/Ws17143Display.hpp"
#include "application/Hardware/Heater/ThermistorHeater/ThermistorHeater.hpp"
#include "application/Hardware/Rotator/DcMotorRotator/DcMotorRotator.hpp"
#include "application/Hardware/TouchController/Xpt2046TouchController/Xpt2046TouchController.hpp"
#include "application/Logger/UartLogger/UartLogger.hpp"
#include "application/Spi/Spi.hpp"
#include "main.h"

extern SPI_HandleTypeDef hspi1;
extern UART_HandleTypeDef huart1;

namespace ATC {
class TargetBoard : public Board {
private:
    Uart uart {huart1};
    UartLogger uartLogger {uart};

    XAxis xAxis_ {uartLogger};
    YAxis yAxis_ {uartLogger};
    ZAxis zAxis_ {uartLogger};
    DcMotorRotator rotator_ {uartLogger};
    ThermistorHeater heater_ {uartLogger};

    FlexibleMemoryController flexibleMemoryController_ {
        0x60000000,
        0x60000002
    };
    DelayProvider delayProvider_ {};
    GpioPin lcdResetPin_ {*LCD_RS_GPIO_Port, LCD_RS_Pin};
    Ws17143DisplayPinout pinout_ {.lcdResetPin_ = lcdResetPin_};
    Ws17143Display display_ {
        pinout_,
        flexibleMemoryController_,
        delayProvider_
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
        Rectangle {
                   .xStart_ = 130,
                   .xEnd_ = 1900,
                   .yStart_ = 80,
                   .yEnd_ = 1950
        },
        Vector2 {.x_ = 480, .y_ = 800}
    };

    BoardDevices targetDevices_ {
        .xAxis = xAxis_,
        .yAxis = yAxis_,
        .zAxis = zAxis_,
        .rotator = rotator_,
        .heater = heater_,
        .display = display_,
        .touchController = touchController_
    };

    TargetBoard();

public:
    static TargetBoard& getBoard();
};
}