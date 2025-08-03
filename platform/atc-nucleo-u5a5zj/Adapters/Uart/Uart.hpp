#pragma once

#include "application/Ports/IUart.hpp"
#include "main.h"

namespace ATC {
class Uart : public IUart {
private:
    UART_HandleTypeDef& handle_;

public:
    Uart(UART_HandleTypeDef& handle);

    virtual void write(const std::span<const char>& data) override;
    virtual void read(const std::span<char>& outputBuffer) override;
};
}