#include "FakeResistiveTouchPanel.hpp"

#include "application/Utils/Logger.hpp"

namespace ATC {
FakeResistiveTouchPanel::FakeResistiveTouchPanel(
    ILoggerSink& loggerSink
) :
    loggerSink_(loggerSink) {}

void FakeResistiveTouchPanel::init() {
    log(loggerSink_, LogLevel::Debug, "Touch panel initialized");
}

bool FakeResistiveTouchPanel::isTouchDetected() {
    return false;
}

uint16_t FakeResistiveTouchPanel::readRawX() {
    return UINT16_MAX;
}

uint16_t FakeResistiveTouchPanel::readRawY() {
    return UINT16_MAX;
}

uint16_t FakeResistiveTouchPanel::readRawZ() {
    return UINT16_MAX;
}
}