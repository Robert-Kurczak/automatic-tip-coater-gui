#pragma once

#include "application/System/Drivers/LoggerSink/ILoggerSink.hpp"
#include "application/System/Drivers/Motor/IMotor.hpp"

#include <string>

namespace ATC {
class FakeMotor : public IMotor {
private:
    ILoggerSink& loggerSink_;
    const std::string name_;

    bool isDirectionClockwise_ = true;

public:
    FakeMotor(ILoggerSink& loggerSink, std::string&& name);

    virtual void init() override;

    virtual void startRotation(uint8_t speedPercent) override;
    virtual void stopRotation() override;

    virtual void setDirectionClockwise() override;
    virtual void setDirectionCounterClockwise() override;
    virtual bool isDirectionClockwise() const override;

    virtual bool isFaultDetected() override;
};
}