#include "HeaterTestTask.hpp"

namespace ATC {
HeaterTestTask::HeaterTestTask(
    ILogger& logger,
    IHeaterController& heaterController
) :
    logger_(logger),
    heaterController_(heaterController_) {}

void HeaterTestTask::start() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
}

void HeaterTestTask::reset() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
}

void HeaterTestTask::tick() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
}

bool HeaterTestTask::isFinished() const {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
    return false;
}

HeaterTestResults HeaterTestTask::consumeResult() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
    return {.temperatureSuccess = true};
}
};