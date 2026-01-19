#pragma once

#include "application/System/Drivers/LoggerSink/ILoggerSink.hpp"
#include "application/System/Drivers/StepperDriver/IStepperDriver.hpp"

#include <cstdint>
#include <string>

namespace ATC {
class FakeStepperDriver : public IStepperDriver {
private:
    ILoggerSink& loggerSink_;
    const std::string name_;

    uint32_t toggleMicroseconds_ = 0;
    bool isDirectionClockwise_ = true;

public:
    FakeStepperDriver(ILoggerSink& loggerSink, std::string&& name);

    void init() override;

    void startStepping() override;
    void stopStepping() override;

    void setMicrosecondsBetweenStepToggle(uint32_t value) override;

    void setDirectionClockwise() override;
    void setDirectionCounterClockwise() override;

    [[nodiscard]] bool isFaultDetected() const override;
};
}