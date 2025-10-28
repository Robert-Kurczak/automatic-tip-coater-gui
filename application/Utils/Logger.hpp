#pragma once

#include <array>
#include <format>
#include <source_location>
#include <stdint.h>

namespace ATC {
inline constexpr bool LOGGER_ENABLED = true;
inline constexpr uint32_t LOG_BUFFER_SIZE = 1024;

enum class LogLevel { Error, Debug, Info };

template<typename SinkType, typename... Args>
void logFormat(
    SinkType& sink,
    std::format_string<Args...> format,
    Args&&... args
) {
    if constexpr (!LOGGER_ENABLED) {
        return;
    }

    std::array<char, LOG_BUFFER_SIZE> formatBuffer;

    const std::format_to_n_result result = std::format_to_n(
        formatBuffer.begin(),
        formatBuffer.size() - 1,
        format,
        std::forward<Args>(args)...
    );
    *result.out = '\0';

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

    logFormat(sink, "[{}] ", logLevelString);
}

template<typename SinkType>
void logSourceLocationLabels(
    SinkType& sink,
    const std::source_location& sourceLocation
) {
    logFormat(
        sink,
        "[{}][{}] ",
        sourceLocation.function_name(),
        sourceLocation.line()
    );
}

template<typename SinkType, typename... Args>
void log(
    SinkType& sink,
    LogLevel logLevel,
    const std::source_location& sourceLocation,
    std::format_string<Args...> format,
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
    std::format_string<Args...> format,
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