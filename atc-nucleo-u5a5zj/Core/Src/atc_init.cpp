#include "application/TouchControllerXpt2046/TouchControllerXpt2046.hpp"
#include "main.h"
#include "touchgfx/hal/OSWrappers.hpp"

#include <stdio.h>

extern SPI_HandleTypeDef hspi1;
extern UART_HandleTypeDef huart1;

Spi spi {hspi1};
GpioPin touchControllerChipSelectPin {
    *TouchPanel_CS_GPIO_Port,
    TouchPanel_CS_Pin
};
TouchControllerXpt2046 touchController {
    spi,
    touchControllerChipSelectPin,
    480,
    800,
    2047,
    2047
};

void debug_print(const char* string) {
    while (*string) {
        while (__HAL_UART_GET_FLAG(&huart1, UART_FLAG_TXE) == RESET)
            ;
        HAL_UART_Transmit(&huart1, (const uint8_t*) &(*string++), 1, HAL_MAX_DELAY);
    }
}

void ATC_Init() {}

void ATC_Loop() {
    touchgfx::OSWrappers::signalVSync();

    char str[256];
    sprintf(
        str,
        "x: %d, y: %d | x: %dpx, y: %dpx\r\n",
        touchController.readRawX(),
        touchController.readRawY(),
        touchController.readX(),
        touchController.readY()
    );
    debug_print(str);
}
