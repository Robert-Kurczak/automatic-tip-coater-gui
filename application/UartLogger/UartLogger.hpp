#pragma once
#include "main.h"

#include <stdint.h>
#include <stdio.h>

extern UART_HandleTypeDef huart1;

namespace UartLogger {
template<typename... Arg>
void debugPrint(const char* string, Arg... args) {
    char buffer[5000];
    sprintf(buffer, string, args...);

    const char* constBuffer = buffer;

    while (*constBuffer) {
        while (__HAL_UART_GET_FLAG(&huart1, UART_FLAG_TXE) == RESET)
            ;
        HAL_UART_Transmit(
            &huart1, (const uint8_t*) &(*constBuffer++), 1, HAL_MAX_DELAY
        );
    }

    const char* newLineBuffer = "\r\n";
    HAL_UART_Transmit(
        &huart1, (const uint8_t*) &(*newLineBuffer++), 1, HAL_MAX_DELAY
    );
    HAL_UART_Transmit(
        &huart1, (const uint8_t*) &(*newLineBuffer++), 1, HAL_MAX_DELAY
    );
}
};