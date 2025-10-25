#pragma once

#include <array>
#include <source_location>
#include <stdint.h>

namespace ATC {
inline constexpr bool LOGGER_ENABLED = true;
inline constexpr uint32_t LOG_BUFFER_SIZE = 1024;

enum class LogLevel { Error, Debug, Info };

template<typename SinkType, typename... Args>
void logFormat(SinkType& sink, const char* format, Args&&... args) {
    if constexpr (!LOGGER_ENABLED) {
        return;
    }

    std::array<char, LOG_BUFFER_SIZE> formatBuffer;
    snprintf(
        formatBuffer.data(),
        formatBuffer.size(),
        format,
        std::forward<Args>(args)...
    );

    sink << formatBuffer.data();
}

template<typename SinkType>
void logNewLine(SinkType& sink) {
    sink << "\r\n";
}

template<typename SinkType>
void logLevelLabel(SinkType& sink, LogLevel logLevel) {
    static constexpr const char* enumNamesArray[] {
        "ERROR", "DEBUG", "INFO"
    };

    const char* logLevelString =
        enumNamesArray[static_cast<uint8_t>(logLevel)];

    logFormat(sink, "[%s] ", logLevelString);
}

template<typename SinkType>
void logSourceLocationLabels(
    SinkType& sink,
    const std::source_location& sourceLocation
) {
    logFormat(
        sink,
        "[%s][%u] ",
        sourceLocation.function_name(),
        sourceLocation.line()
    );
}

template<typename SinkType, typename... Args>
void log(
    SinkType& sink,
    LogLevel logLevel,
    const std::source_location& sourceLocation,
    const char* format,
    Args&&... args
) {
    if constexpr (!LOGGER_ENABLED) {
        return;
    }

    logLevelLabel(sink, logLevel);
    logSourceLocationLabels(sink, sourceLocation);
    logFormat(sink, format, std::forward<Args>(args)...);
    logNewLine(sink);
}

template<typename SinkType, typename... Args>
void log(
    SinkType& sink,
    LogLevel logLevel,
    const char* format,
    Args&&... args
) {
    if constexpr (!LOGGER_ENABLED) {
        return;
    }

    logLevelLabel(sink, logLevel);
    logFormat(sink, format, std::forward<Args>(args)...);
    logNewLine(sink);
}
}