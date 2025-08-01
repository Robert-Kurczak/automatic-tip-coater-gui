#pragma once

#include <functional>
#include <source_location>
#include <string>
#include <string_view>

namespace ATC {

enum class LOG_LEVEL { INFO_LOG, DEBUG_LOG, ERROR_LOG };

// TODO replace std::function with embedded friendly alternative

class ILogger {
public:
    virtual void log(LOG_LEVEL logLevel, const std::string_view text) = 0;

    virtual void log(
        LOG_LEVEL logLevel,
        const std::source_location& sourceLocation,
        const std::string_view text
    ) = 0;

    virtual void log(
        LOG_LEVEL logLevel,
        const std::function<std::string_view()>& textBuilder
    ) = 0;

    virtual void log(
        LOG_LEVEL logLevel,
        const std::source_location& sourceLocation,
        const std::function<std::string_view()>& textBuilder
    ) = 0;
};
}