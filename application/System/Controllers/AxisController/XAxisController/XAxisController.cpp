#include "XAxisController.hpp"

#include <source_location>

namespace ATC {
XAxisController::XAxisController(ILogger& logger) : logger_(logger) {}

void XAxisController::init() {}

void XAxisController::tick() {}

bool XAxisController::wasFaultReported() const {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
    return false;
}

void XAxisController::moveToMinLimitPosition() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
}

bool XAxisController::isAtMinLimitPosition() const {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
    return false;
}

void XAxisController::moveToMaxLimitPosition() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
}

bool XAxisController::isAtMaxLimitPosition() const {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
    return false;
}

void XAxisController::moveToHomePosition() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
}

bool XAxisController::isAtHomePosition() const {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
    return true;
}

void XAxisController::moveToStartPosition() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
}

bool XAxisController::isAtStartPosition() const {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
    return false;
}

void XAxisController::moveToEndPosition() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
}

bool XAxisController::isAtEndPosition() const {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
    return false;
}

void XAxisController::moveToHeaterFrontPosition() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
}

bool XAxisController::isAtHeaterFrontPosition() const {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
    return false;
}

void XAxisController::setStartPosition(uint32_t value) {
    startPosition_ = value;
}

uint32_t XAxisController::getStartPosition() const {
    return startPosition_;
}

void XAxisController::setEndPosition(uint32_t value) {
    endPosition_ = value;
}

uint32_t XAxisController::getEndPosition() const {
    return endPosition_;
}

void XAxisController::setSpeed(uint32_t value) {
    speed_ = value;
}

uint32_t XAxisController::getSpeed() const {
    return speed_;
}
}