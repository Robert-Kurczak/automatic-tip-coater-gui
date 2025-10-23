#pragma once

#include "application/System/Drivers/Logger/ILogger.hpp"

namespace ATC {
class FakeLogger : public ILogger {
public:
    virtual void log(
        LOG_LEVEL logLevel,
        const std::string_view text
    ) override;

    virtual void log(
        LOG_LEVEL logLevel,
        const std::source_location& sourceLocation,
        const std::string_view text
    ) override;

    virtual void log(
        LOG_LEVEL logLevel,
        const std::function<std::string_view()>& textBuilder
    ) override;

    virtual void log(
        LOG_LEVEL logLevel,
        const std::source_location& sourceLocation,
        const std::function<std::string_view()>& textBuilder
    ) override;
};
}