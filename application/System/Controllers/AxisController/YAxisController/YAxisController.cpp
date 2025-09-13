#include "YAxisController.hpp"

#include <source_location>

namespace ATC {
YAxisController::YAxisController(ILogger& logger) : logger_(logger) {}

void YAxisController::init() {}

void YAxisController::tick() {}

bool YAxisController::wasFaultReported() const {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
    return false;
}

void YAxisController::moveToMinLimitPosition() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
}

bool YAxisController::isAtMinLimitPosition() const {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
    return false;
}

void YAxisController::moveToMaxLimitPosition() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
}

bool YAxisController::isAtMaxLimitPosition() const {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
    return false;
}

void YAxisController::moveToHomePosition() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
}

bool YAxisController::isAtHomePosition() const {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
    return true;
}

void YAxisController::moveToStartPosition() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
}

bool YAxisController::isAtStartPosition() const {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
    return false;
}

void YAxisController::moveToEndPosition() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
}

bool YAxisController::isAtEndPosition() const {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
    return false;
}

void YAxisController::moveToDetectTip() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
}

bool YAxisController::isTipDetected() const {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
    return false;
}

void YAxisController::moveToCoatingPosition() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
}

bool YAxisController::isAtCoatingPosition() const {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
    return false;
}

void YAxisController::setStartPosition(uint32_t value) {
    startPosition_ = value;
}

uint32_t YAxisController::getStartPosition() const {
    return startPosition_;
}

void YAxisController::setEndPosition(uint32_t value) {
    endPosition_ = value;
}

uint32_t YAxisController::getEndPosition() const {
    return endPosition_;
}

void YAxisController::setSpeed(uint32_t value) {
    speed_ = value;
}

uint32_t YAxisController::getSpeed() const {
    return speed_;
}
}