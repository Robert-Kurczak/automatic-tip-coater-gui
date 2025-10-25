#include "XAxisController.hpp"

#include "application/Utils/Logger.hpp"

#include <source_location>

namespace ATC {
XAxisController::XAxisController(ILoggerSink& loggerSink) :
    loggerSink_(loggerSink) {}

void XAxisController::init(const AxisPersistentConfig& config) {
    startPosition_ = config.startPosition;
    endPosition_ = config.endPosition;
    speed_ = config.speed;
}

void XAxisController::tick() {}

bool XAxisController::wasFaultReported() const {
    log(loggerSink_,
        LogLevel::Error,
        std::source_location::current(),
        "Not implemented");
    // TODO implement
    return false;
}

void XAxisController::moveToPosition(uint32_t position) {
    log(loggerSink_,
        LogLevel::Error,
        std::source_location::current(),
        "Not implemented");
    // TODO implement
}

uint32_t XAxisController::getCurrentPosition() const {
    log(loggerSink_,
        LogLevel::Error,
        std::source_location::current(),
        "Not implemented");
    // TODO implement
    return 0;
}

void XAxisController::moveToMinLimitPosition() {
    log(loggerSink_,
        LogLevel::Error,
        std::source_location::current(),
        "Not implemented");
    // TODO implement
}

bool XAxisController::isAtMinLimitPosition() const {
    log(loggerSink_,
        LogLevel::Error,
        std::source_location::current(),
        "Not implemented");
    // TODO implement
    return false;
}

void XAxisController::moveToMaxLimitPosition() {
    log(loggerSink_,
        LogLevel::Error,
        std::source_location::current(),
        "Not implemented");
    // TODO implement
}

bool XAxisController::isAtMaxLimitPosition() const {
    log(loggerSink_,
        LogLevel::Error,
        std::source_location::current(),
        "Not implemented");
    // TODO implement
    return false;
}

void XAxisController::moveToHomePosition() {
    log(loggerSink_,
        LogLevel::Error,
        std::source_location::current(),
        "Not implemented");
    // TODO implement
}

bool XAxisController::isAtHomePosition() const {
    log(loggerSink_,
        LogLevel::Error,
        std::source_location::current(),
        "Not implemented");
    // TODO implement
    return true;
}

void XAxisController::moveToStartPosition() {
    log(loggerSink_,
        LogLevel::Error,
        std::source_location::current(),
        "Not implemented");
    // TODO implement
}

bool XAxisController::isAtStartPosition() const {
    log(loggerSink_,
        LogLevel::Error,
        std::source_location::current(),
        "Not implemented");
    // TODO implement
    return false;
}

void XAxisController::moveToEndPosition() {
    log(loggerSink_,
        LogLevel::Error,
        std::source_location::current(),
        "Not implemented");
    // TODO implement
}

bool XAxisController::isAtEndPosition() const {
    log(loggerSink_,
        LogLevel::Error,
        std::source_location::current(),
        "Not implemented");
    // TODO implement
    return false;
}

void XAxisController::moveToHeaterFrontPosition() {
    log(loggerSink_,
        LogLevel::Error,
        std::source_location::current(),
        "Not implemented");
    // TODO implement
}

bool XAxisController::isAtHeaterFrontPosition() const {
    log(loggerSink_,
        LogLevel::Error,
        std::source_location::current(),
        "Not implemented");
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