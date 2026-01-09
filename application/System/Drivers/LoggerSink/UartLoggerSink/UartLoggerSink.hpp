#pragma once

#include "../ILoggerSink.hpp"
#include "application/System/Ports/IUart.hpp"

namespace ATC {
class UartLoggerSink : public ILoggerSink {
private:
    IUart& uart_;

public:
    UartLoggerSink(IUart& uart);

    ILoggerSink& operator<<(std::string_view text) override;
};
}