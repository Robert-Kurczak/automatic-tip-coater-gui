#pragma once

#include <string_view>

namespace ATC {
class ILoggerSink {
public:
    ILoggerSink() = default;
    ILoggerSink(const ILoggerSink&) = delete;
    ILoggerSink& operator=(const ILoggerSink&) = delete;
    ILoggerSink(ILoggerSink&&) = delete;
    ILoggerSink& operator=(ILoggerSink&&) = delete;
    virtual ~ILoggerSink() = default;

    virtual ILoggerSink& operator<<(std::string_view text) = 0;
};
}