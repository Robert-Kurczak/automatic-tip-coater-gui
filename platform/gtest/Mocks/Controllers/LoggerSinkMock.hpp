#pragma once

#include "application/System/Drivers/LoggerSink/ILoggerSink.hpp"

#include <string>
#include <string_view>

namespace ATC {
class LoggerSinkMock : public ILoggerSink {
public:
    std::string buffer;

    ILoggerSink& operator<<(std::string_view text) override {
        buffer += text;
        return *this;
    }
};
}