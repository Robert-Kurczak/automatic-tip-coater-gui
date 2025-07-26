#pragma once

#include "application/Board/Board.hpp"
#include "application/Board/BoardDevices.hpp"
#include "application/GpioPin/GpioPin.hpp"
#include "application/Hardware/Axes/XAxis/XAxis.hpp"
#include "application/Hardware/Axes/YAxis/YAxis.hpp"
#include "application/Hardware/Axes/ZAxis/ZAxis.hpp"
#include "application/Heater/Heater.hpp"
#include "application/Rotator/Rotator.hpp"
#include "application/Spi/Spi.hpp"
#include "application/TouchControllerXpt2046/TouchControllerXpt2046.hpp"
#include "main.h"

extern SPI_HandleTypeDef hspi1;
extern UART_HandleTypeDef huart1;

namespace ATC {

class TargetBoard : public Board {
private:
    XAxis xAxis_ {};
    YAxis yAxis_ {};
    ZAxis zAxis_ {};
    Rotator rotator_ {};
    Heater heater_ {};

    FlexibleMemoryController flexibleMemoryController_ {
        0x60000000,
        0x60000002
    };
    DelayProvider delayProvider_ {};
    GpioPin lcdResetPin_ {*LCD_RS_GPIO_Port, LCD_RS_Pin};
    Ws17143Pinout pinout_ {.lcdResetPin_ = lcdResetPin_};
    DisplayWs17143 display_ {
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
    Xpt2046Pinout xpt2046Pinout_ {
        .chipSelectPin_ = touchControllerChipSelectPin_,
        .touchInterruptPin_ = touchControllerInterruptPin_
    };
    TouchControllerXpt2046 touchController_ {
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