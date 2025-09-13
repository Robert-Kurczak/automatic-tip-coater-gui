#include "ZAxisController.hpp"

#include <source_location>

namespace ATC {
ZAxisController::ZAxisController(ILogger& logger) : logger_(logger) {}

void ZAxisController::init() {}

void ZAxisController::tick() {}

void ZAxisController::moveToHomePosition() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
}

bool ZAxisController::isAtHomePosition() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
    return true;
}

void ZAxisController::moveToStartPosition() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
}

bool ZAxisController::isAtStartPosition() const {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
    return false;
}

void ZAxisController::moveToEndPosition() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
}

bool ZAxisController::isAtEndPosition() const {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
    return false;
}

void ZAxisController::setStartPosition(uint32_t value) {
    startPosition_ = value;
}

uint32_t ZAxisController::getStartPosition() const {
    return startPosition_;
}

void ZAxisController::setEndPosition(uint32_t value) {
    endPosition_ = value;
}

uint32_t ZAxisController::getEndPosition() const {
    return endPosition_;
}

void ZAxisController::setSpeed(uint32_t value) {
    speed_ = value;
}

uint32_t ZAxisController::getSpeed() const {
    return speed_;
}
}