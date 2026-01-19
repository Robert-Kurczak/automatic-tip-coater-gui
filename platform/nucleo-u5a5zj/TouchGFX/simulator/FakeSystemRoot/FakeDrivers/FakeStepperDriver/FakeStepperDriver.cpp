#include "FakeStepperDriver.hpp"

#include "application/Utils/Logger.hpp"

#include <cstdint>

namespace ATC {
FakeStepperDriver::FakeStepperDriver(
    ILoggerSink& loggerSink,
    std::string&& name
) :
    loggerSink_(loggerSink),
    name_(name) {}

void FakeStepperDriver::init() {
    log(loggerSink_, LogLevel::Debug, "{} initialized", name_);
}

void FakeStepperDriver::startStepping() {
    log(loggerSink_, LogLevel::Debug, "{} started stepping", name_);
}

void FakeStepperDriver::stopStepping() {
    log(loggerSink_, LogLevel::Debug, "{} stopped stepping", name_);
}

void FakeStepperDriver::setMicrosecondsBetweenStepToggle(uint32_t value) {
    toggleMicroseconds_ = value;

    log(loggerSink_,
        LogLevel::Debug,
        "{} toggle microseconds seto to {}",
        name_,
        value);
}

void FakeStepperDriver::setDirectionClockwise() {
    isDirectionClockwise_ = true;

    log(loggerSink_,
        LogLevel::Debug,
        "Clockwise direction set for {}",
        name_);
}

void FakeStepperDriver::setDirectionCounterClockwise() {
    isDirectionClockwise_ = false;

    log(loggerSink_,
        LogLevel::Debug,
        "Counter clockwise direction set for {}",
        name_);
}

[[nodiscard]] bool FakeStepperDriver::isFaultDetected() const {
    static uint16_t methodCalls = 0;
    methodCalls++;

    if (methodCalls >= UINT16_MAX / 2) {
        log(loggerSink_,
            LogLevel::Debug,
            "Reporting {} driver fault",
            name_);

        return true;
    }

    return false;
}
}