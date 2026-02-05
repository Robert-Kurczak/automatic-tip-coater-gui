#include "FakeMotorDriver.hpp"

#include "application/Utils/Logger.hpp"

namespace ATC {
FakeMotorDriver::FakeMotorDriver(
    ILoggerSink& loggerSink,
    std::string&& name
) :
    loggerSink_(loggerSink),
    name_(std::move(name)) {}

void FakeMotorDriver::init() {
    log(loggerSink_, LogLevel::Debug, "{} initialized", name_);
}

void FakeMotorDriver::startRotation(uint8_t speedPercent) {
    log(loggerSink_, LogLevel::Debug, "{} started", name_);
}
void FakeMotorDriver::stopRotation() {
    log(loggerSink_, LogLevel::Debug, "{} stopped", name_);
}

void FakeMotorDriver::setDirectionClockwise() {
    isDirectionClockwise_ = true;

    log(loggerSink_,
        LogLevel::Debug,
        "Clockwise direction set for {}",
        name_);
}

void FakeMotorDriver::setDirectionCounterClockwise() {
    isDirectionClockwise_ = false;

    log(loggerSink_,
        LogLevel::Debug,
        "Counter clockwise direction set for {}",
        name_);
}

bool FakeMotorDriver::isDirectionClockwise() const {
    return isDirectionClockwise_;
}

bool FakeMotorDriver::isFaultDetected() {
    static uint16_t methodCalls = 0;
    methodCalls++;

    if (methodCalls >= 1000) {
        log(loggerSink_, LogLevel::Debug, "Reporting {} fault", name_);

        return true;
    }

    return false;
}
}