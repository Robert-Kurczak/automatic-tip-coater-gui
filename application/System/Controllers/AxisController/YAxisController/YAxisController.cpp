#include "YAxisController.hpp"

#include "application/Utils/Logger.hpp"

#include <source_location>

namespace ATC {
YAxisController::YAxisController(ILoggerSink& loggerSink) :
    loggerSink_(loggerSink) {}

void YAxisController::init(const AxisPersistentConfig& config) {
    startPosition_ = config.startPosition;
    endPosition_ = config.endPosition;
    speed_ = config.speed;
}

void YAxisController::tick() {}

bool YAxisController::wasFaultReported() const {
    log(loggerSink_,
        LogLevel::Error,
        std::source_location::current(),
        "Not implemented");
    // TODO implement
    return false;
}

void YAxisController::moveToPosition(uint32_t position) {
    log(loggerSink_,
        LogLevel::Error,
        std::source_location::current(),
        "Not implemented");
    // TODO implement
}

uint32_t YAxisController::getCurrentPosition() const {
    log(loggerSink_,
        LogLevel::Error,
        std::source_location::current(),
        "Not implemented");
    // TODO implement
    return 0;
}

void YAxisController::moveToMinLimitPosition() {
    log(loggerSink_,
        LogLevel::Error,
        std::source_location::current(),
        "Not implemented");
    // TODO implement
}

bool YAxisController::isAtMinLimitPosition() const {
    log(loggerSink_,
        LogLevel::Error,
        std::source_location::current(),
        "Not implemented");
    // TODO implement
    return false;
}

void YAxisController::moveToMaxLimitPosition() {
    log(loggerSink_,
        LogLevel::Error,
        std::source_location::current(),
        "Not implemented");
    // TODO implement
}

bool YAxisController::isAtMaxLimitPosition() const {
    log(loggerSink_,
        LogLevel::Error,
        std::source_location::current(),
        "Not implemented");
    // TODO implement
    return false;
}

void YAxisController::moveToHomePosition() {
    log(loggerSink_,
        LogLevel::Error,
        std::source_location::current(),
        "Not implemented");
    // TODO implement
}

bool YAxisController::isAtHomePosition() const {
    log(loggerSink_,
        LogLevel::Error,
        std::source_location::current(),
        "Not implemented");
    // TODO implement
    return true;
}

void YAxisController::moveToStartPosition() {
    log(loggerSink_,
        LogLevel::Error,
        std::source_location::current(),
        "Not implemented");
    // TODO implement
}

bool YAxisController::isAtStartPosition() const {
    log(loggerSink_,
        LogLevel::Error,
        std::source_location::current(),
        "Not implemented");
    // TODO implement
    return false;
}

void YAxisController::moveToEndPosition() {
    log(loggerSink_,
        LogLevel::Error,
        std::source_location::current(),
        "Not implemented");
    // TODO implement
}

bool YAxisController::isAtEndPosition() const {
    log(loggerSink_,
        LogLevel::Error,
        std::source_location::current(),
        "Not implemented");
    // TODO implement
    return false;
}

void YAxisController::moveToDetectTip() {
    log(loggerSink_,
        LogLevel::Error,
        std::source_location::current(),
        "Not implemented");
    // TODO implement
}

bool YAxisController::isTipDetected() const {
    log(loggerSink_,
        LogLevel::Error,
        std::source_location::current(),
        "Not implemented");
    // TODO implement
    return false;
}

void YAxisController::moveToCoatingPosition() {
    log(loggerSink_,
        LogLevel::Error,
        std::source_location::current(),
        "Not implemented");
    // TODO implement
}

bool YAxisController::isAtCoatingPosition() const {
    log(loggerSink_,
        LogLevel::Error,
        std::source_location::current(),
        "Not implemented");
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