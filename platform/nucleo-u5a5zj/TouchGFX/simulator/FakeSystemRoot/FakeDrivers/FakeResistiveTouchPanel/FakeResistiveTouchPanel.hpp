#pragma once

#include "application/System/Drivers/LoggerSink/ILoggerSink.hpp"
#include "application/System/Drivers/ResistiveTouchPanel/IResistiveTouchPanel.hpp"

namespace ATC {
class FakeResistiveTouchPanel : public IResistiveTouchPanel {
private:
    ILoggerSink& loggerSink_;

public:
    FakeResistiveTouchPanel(ILoggerSink& loggerSink);

    virtual void init() override;

    virtual bool isTouchDetected() override;

    virtual uint16_t readRawX() override;
    virtual uint16_t readRawY() override;
    virtual uint16_t readRawZ() override;
};
}