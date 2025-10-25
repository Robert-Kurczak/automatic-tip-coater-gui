#include "FakeDisplay.hpp"

#include "application/Utils/Logger.hpp"

namespace ATC {

FakeDisplay::FakeDisplay(ILoggerSink& loggerSink) :
    loggerSink_(loggerSink) {}

void FakeDisplay::init() {
    log(loggerSink_, LogLevel::Debug, "Display initialized");
}

void FakeDisplay::drawTestPattern(uint8_t seed) {
    log(loggerSink_, LogLevel::Debug, "Displat test: [%u]", seed);
}

void FakeDisplay::draw(
    const std::span<const uint16_t>& framebuffer,
    const Rectangle& window
) {}

void FakeDisplay::draw(const std::span<const uint16_t>& framebuffer) {}
}