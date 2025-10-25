#pragma once

#include "application/System/Drivers/Display/IDisplay.hpp"
#include "application/System/Drivers/LoggerSink/ILoggerSink.hpp"

namespace ATC {
class FakeDisplay : public IDisplay {
private:
    ILoggerSink& loggerSink_;

public:
    FakeDisplay(ILoggerSink& loggerSink);

    virtual void init() override;
    virtual void drawTestPattern(uint8_t seed) override;
    virtual void draw(
        const std::span<const uint16_t>& framebuffer,
        const Rectangle& window
    ) override;
    virtual void draw(
        const std::span<const uint16_t>& framebuffer
    ) override;
};
}