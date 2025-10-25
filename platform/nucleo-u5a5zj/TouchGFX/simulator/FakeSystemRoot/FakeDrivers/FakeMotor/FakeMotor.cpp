#include "FakeMotor.hpp"

#include "application/Utils/Logger.hpp"

namespace ATC {
FakeMotor::FakeMotor(ILoggerSink& loggerSink, std::string&& name) :
    loggerSink_(loggerSink),
    name_(std::move(name)) {}

void FakeMotor::init() {
    log(loggerSink_, LogLevel::Debug, "%s initialized", name_);
}

void FakeMotor::startRotation(uint8_t speedPercent) {
    log(loggerSink_, LogLevel::Debug, "%s started", name_);
}
void FakeMotor::stopRotation() {
    log(loggerSink_, LogLevel::Debug, "%s stopped", name_);
}

void FakeMotor::setDirectionClockwise() {
    isDirectionClockwise_ = true;

    log(loggerSink_,
        LogLevel::Debug,
        "Clockwise direction set for %s",
        name_);
}

void FakeMotor::setDirectionCounterClockwise() {
    isDirectionClockwise_ = false;

    log(loggerSink_,
        LogLevel::Debug,
        "Counter clockwise direction set for %s",
        name_);
}

bool FakeMotor::isDirectionClockwise() const {
    return isDirectionClockwise_;
}
}