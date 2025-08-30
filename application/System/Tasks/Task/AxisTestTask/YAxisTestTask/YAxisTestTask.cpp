#include "YAxisTestTask.hpp"

namespace ATC {
YAxisTestTask::YAxisTestTask(ILogger& logger) : logger_(logger) {}

void YAxisTestTask::start() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
}

void YAxisTestTask::reset() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
}

void YAxisTestTask::tick() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
}

bool YAxisTestTask::isFinished() const {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
    return false;
}

AxisTestResults YAxisTestTask::consumeResult() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
    return {
        .startLimitSwitchSuccess = true,
        .endLimitSwitchSuccess = true,
        .motorDriverSuccess = false
    };
}
};