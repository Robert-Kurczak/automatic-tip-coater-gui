#pragma once

#include <string_view>

namespace ATC {
class ILoggerSink {
public:
    virtual ~ILoggerSink() = default;
    virtual ILoggerSink& operator<<(std::string_view text) = 0;
};
}