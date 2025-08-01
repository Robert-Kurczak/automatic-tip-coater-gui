#include "Uart.hpp"

namespace ATC {
Uart::Uart(UART_HandleTypeDef& handle) : handle_(handle) {}

void Uart::write(const std::span<const char>& data) {
    HAL_UART_Transmit(
        &handle_,
        reinterpret_cast<const uint8_t*>(data.data()),
        data.size(),
        HAL_MAX_DELAY
    );
}

void Uart::read(const std::span<char>& outputBuffer) {
    HAL_UART_Receive(
        &handle_,
        reinterpret_cast<uint8_t*>(outputBuffer.data()),
        outputBuffer.size(),
        HAL_MAX_DELAY
    );
}
}