#include "XAxisTestTask.hpp"

namespace ATC {
XAxisTestTask::XAxisTestTask(ILogger& logger) : logger_(logger) {}

void XAxisTestTask::start() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
}

void XAxisTestTask::reset() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
}

void XAxisTestTask::tick() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
}

bool XAxisTestTask::isFinished() const {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
    return false;
}

AxisTestResults XAxisTestTask::consumeResult() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
    return {
        .startLimitSwitchSuccess = true,
        .endLimitSwitchSuccess = false,
        .motorDriverSuccess = true
    };
}
};