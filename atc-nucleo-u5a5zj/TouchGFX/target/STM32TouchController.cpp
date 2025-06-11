/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : STM32TouchController.cpp
  ******************************************************************************
  * This file was created by TouchGFX Generator 4.25.0. This file is only
  * generated once! Delete this file from your project and re-generate code
  * using STM32CubeMX or change this file manually to update it.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* USER CODE BEGIN STM32TouchController */

#include <STM32TouchController.hpp>
#include <stdio.h>
#include "application/TouchControllerXpt2046/TouchControllerXpt2046.hpp"
#include "main.h"

using namespace ATC;

extern SPI_HandleTypeDef hspi1;
extern UART_HandleTypeDef huart1;

Spi spi {hspi1};
GpioPin touchControllerChipSelectPin {
    *TouchPanel_CS_GPIO_Port,
    TouchPanel_CS_Pin
};
GpioPin touchControllerInterruptPin {
    *TouchPanel_IRQ_GPIO_Port,
    TouchPanel_IRQ_Pin
};
Xpt2046Pinout xpt2046Pinout {
    .chipSelectPin_ = touchControllerChipSelectPin,
    .touchInterruptPin_ = touchControllerInterruptPin
};
TouchControllerXpt2046 touchController {
    xpt2046Pinout,
    spi,
    Rectangle {
        .xStart_ = 130,
        .xEnd_ = 1900,
        .yStart_ = 80,
        .yEnd_ = 1950
    },
    Vector2 {.x_ = 480, .y_ = 800}
};

void debug_print(const char* string) {
    while (*string) {
        while (__HAL_UART_GET_FLAG(&huart1, UART_FLAG_TXE) == RESET)
            ;
        HAL_UART_Transmit(&huart1, (const uint8_t*) &(*string++), 1, HAL_MAX_DELAY);
    }
}

void STM32TouchController::init()
{
    touchController.init();
}

bool STM32TouchController::sampleTouch(int32_t& x, int32_t& y)
{
    /**
     * By default sampleTouch returns false,
     * return true if a touch has been detected, otherwise false.
     *
     * Coordinates are passed to the caller by reference by x and y.
     *
     * This function is called by the TouchGFX framework.
     * By default sampleTouch is called every tick, this can be adjusted by HAL::setTouchSampleRate(int8_t);
     *
     */

    if (touchController.isTouched()) {
        x = touchController.readX();
        y = 800 - touchController.readY();

        char str[2048];
        sprintf(
            str,
            "x: %d, y: %d | raw x: %d, raw y: %d, raw z: %d\r\n",
            x,
            y,
            touchController.readRawX(),
            touchController.readRawY(),
            touchController.readRawPressure()
        );
        debug_print(str);

        return true;
    }

    return false;
}

/* USER CODE END STM32TouchController */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
