#include "SpindleTestTask.hpp"

namespace ATC {
SpindleTestTask::SpindleTestTask(
    ILogger& logger,
    ISpindleController& spindleController
) :
    logger_(logger),
    spindleController_(spindleController) {}

void SpindleTestTask::start() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
}

void SpindleTestTask::reset() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
}

void SpindleTestTask::tick() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
}

bool SpindleTestTask::isFinished() const {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
    return true;
}

SpindleTestResults SpindleTestTask::consumeResult() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
    return SpindleTestResults{.motorDriverSuccess = true};
}

}
