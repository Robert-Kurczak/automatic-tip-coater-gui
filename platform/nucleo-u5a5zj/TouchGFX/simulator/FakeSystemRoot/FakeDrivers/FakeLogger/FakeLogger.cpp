#include "FakeLogger.hpp"

#include <touchgfx/Utils.hpp>

namespace ATC {
namespace {
inline static constexpr std::string_view enumNamesArray[] {
    "[INFO] ",
    "[DEBUG] ",
    "[ERROR] "
};
}

void FakeLogger::log(LOG_LEVEL logLevel, const std::string_view text) {
    const std::string_view logLevelString =
        enumNamesArray[static_cast<uint8_t>(logLevel)];

    touchgfx_printf("%s\n\r", text);
}

void FakeLogger::log(
    LOG_LEVEL logLevel,
    const std::source_location& sourceLocation,
    const std::string_view text
) {
    const std::string_view logLevelString =
        enumNamesArray[static_cast<uint8_t>(logLevel)];

    touchgfx_printf(
        "[%s][%s][%s] %s\r\n",
        logLevelString,
        sourceLocation.function_name(),
        sourceLocation.line(),
        text
    );
}

void FakeLogger::log(
    LOG_LEVEL logLevel,
    const std::function<std::string_view()>& textBuilder
) {
    log(logLevel, textBuilder());
}

void FakeLogger::log(
    LOG_LEVEL logLevel,
    const std::source_location& sourceLocation,
    const std::function<std::string_view()>& textBuilder
) {
    log(logLevel, sourceLocation, textBuilder);
}
}