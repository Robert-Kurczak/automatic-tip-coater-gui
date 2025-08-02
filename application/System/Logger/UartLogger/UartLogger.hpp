#pragma once
#include "../ILogger.hpp"
#include "application/Ports/IUart.hpp"

#include <stdint.h>
#include <stdio.h>

namespace ATC {
class UartLogger : public ILogger {
private:
    IUart& uart_;

    void logSourceData(std::string_view data);

public:
    UartLogger(IUart& uart);

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