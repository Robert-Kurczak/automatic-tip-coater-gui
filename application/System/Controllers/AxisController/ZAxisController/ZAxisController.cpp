#include "ZAxisController.hpp"

#include "application/Utils/Logger.hpp"

#include <source_location>

namespace ATC {
ZAxisController::ZAxisController(ILoggerSink& loggerSink) :
    loggerSink_(loggerSink) {}

void ZAxisController::init(const AxisPersistentConfig& config) {
    startPosition_ = config.startPosition;
    endPosition_ = config.endPosition;
    speed_ = config.speedInMillimetersPerSecond;
}

void ZAxisController::tick() {}

bool ZAxisController::wasFaultReported() const {
    log(loggerSink_,
        LogLevel::Error,
        std::source_location::current(),
        "Not implemented");
    // TODO implement
    return false;
}

void ZAxisController::moveToPosition(uint32_t position) {
    log(loggerSink_,
        LogLevel::Error,
        std::source_location::current(),
        "Not implemented");
    // TODO implement
}

uint32_t ZAxisController::getCurrentPosition() const {
    log(loggerSink_,
        LogLevel::Error,
        std::source_location::current(),
        "Not implemented");
    // TODO implement
    return 0;
}

void ZAxisController::moveToMinLimitPosition() {
    log(loggerSink_,
        LogLevel::Error,
        std::source_location::current(),
        "Not implemented");
    // TODO implement
}

bool ZAxisController::isAtMinLimitPosition() const {
    log(loggerSink_,
        LogLevel::Error,
        std::source_location::current(),
        "Not implemented");
    // TODO implement
    return false;
}

void ZAxisController::moveToMaxLimitPosition() {
    log(loggerSink_,
        LogLevel::Error,
        std::source_location::current(),
        "Not implemented");
    // TODO implement
}

bool ZAxisController::isAtMaxLimitPosition() const {
    log(loggerSink_,
        LogLevel::Error,
        std::source_location::current(),
        "Not implemented");
    // TODO implement
    return false;
}

void ZAxisController::moveToHomePosition() {
    log(loggerSink_,
        LogLevel::Error,
        std::source_location::current(),
        "Not implemented");
    // TODO implement
}

bool ZAxisController::isAtHomePosition() const {
    log(loggerSink_,
        LogLevel::Error,
        std::source_location::current(),
        "Not implemented");
    // TODO implement
    return true;
}

void ZAxisController::moveToStartPosition() {
    log(loggerSink_,
        LogLevel::Error,
        std::source_location::current(),
        "Not implemented");
    // TODO implement
}

bool ZAxisController::isAtStartPosition() const {
    log(loggerSink_,
        LogLevel::Error,
        std::source_location::current(),
        "Not implemented");
    // TODO implement
    return false;
}

void ZAxisController::moveToEndPosition() {
    log(loggerSink_,
        LogLevel::Error,
        std::source_location::current(),
        "Not implemented");
    // TODO implement
}

bool ZAxisController::isAtEndPosition() const {
    log(loggerSink_,
        LogLevel::Error,
        std::source_location::current(),
        "Not implemented");
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

void ZAxisController::setSpeedInMillimetersPerSecond(uint16_t value) {
    speed_ = value;
}

uint16_t ZAxisController::getSpeedInMillimetersPerSecond() const {
    return speed_;
}
}