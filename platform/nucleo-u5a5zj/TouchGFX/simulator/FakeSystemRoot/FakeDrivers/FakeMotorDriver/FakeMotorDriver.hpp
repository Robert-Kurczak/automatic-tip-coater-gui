#pragma once

#include "application/System/Drivers/LoggerSink/ILoggerSink.hpp"
#include "application/System/Drivers/MotorDriver/IMotorDriver.hpp"

#include <string>

namespace ATC {
class FakeMotorDriver : public IMotorDriver {
private:
    ILoggerSink& loggerSink_;
    const std::string name_;

    bool isDirectionClockwise_ = true;

public:
    FakeMotorDriver(ILoggerSink& loggerSink, std::string&& name);

    virtual void init() override;

    virtual void startRotation(uint8_t speedPercent) override;
    virtual void stopRotation() override;

    virtual void setDirectionClockwise() override;
    virtual void setDirectionCounterClockwise() override;
    virtual bool isDirectionClockwise() const override;

    virtual bool isFaultDetected() override;
};
}
