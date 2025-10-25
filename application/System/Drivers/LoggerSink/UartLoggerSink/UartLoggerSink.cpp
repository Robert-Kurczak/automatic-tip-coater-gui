#include "UartLoggerSink.hpp"

namespace ATC {
UartLoggerSink::UartLoggerSink(IUart& uart) : uart_(uart) {}

ILoggerSink& UartLoggerSink::operator<<(std::string_view text) {
    uart_.write(text);
    return *this;
}
}