#include "UartLogger.hpp"

namespace ATC {
namespace {
inline static constexpr std::string_view enumNamesArray[] {
    "[INFO] ",
    "[DEBUG] ",
    "[ERROR] "
};
}

void UartLogger::logSourceData(std::string_view data) {
    uart_.write("[");
    uart_.write(data);
    uart_.write("]");
}

UartLogger::UartLogger(IUart& uart) : uart_(uart) {}

void UartLogger::log(LOG_LEVEL logLevel, const std::string_view text) {
    const std::string_view logLevelString =
        enumNamesArray[static_cast<uint8_t>(logLevel)];

    uart_.write(logLevelString);
    uart_.write(text);
    uart_.write("\r\n");
}

void UartLogger::log(
    LOG_LEVEL logLevel,
    const std::source_location& sourceLocation,
    const std::string_view text
) {
    const std::string_view logLevelString =
        enumNamesArray[static_cast<uint8_t>(logLevel)];

    uart_.write(logLevelString);

    logSourceData(sourceLocation.function_name());
    logSourceData(std::to_string(sourceLocation.line()));

    uart_.write(" ");
    uart_.write(text);
    uart_.write("\r\n");
}

void UartLogger::log(
    LOG_LEVEL logLevel,
    const std::function<std::string_view()>& textBuilder
) {
    log(logLevel, textBuilder());
}

void UartLogger::log(
    LOG_LEVEL logLevel,
    const std::source_location& sourceLocation,
    const std::function<std::string_view()>& textBuilder
) {
    log(logLevel, sourceLocation, textBuilder);
}
};