#pragma once

#include "ISpindleController.hpp"
#include "application/System/Drivers/LoggerSink/ILoggerSink.hpp"
#include "application/System/Drivers/Motor/IMotor.hpp"
#include "application/System/Ports/ISystemClock.hpp"

#include <stdint.h>

namespace ATC {
class SpindleController : public ISpindleController {
private:
    ILoggerSink& loggerSink_;
    ISystemClock& systemClock_;
    IMotor& motor_;

    uint8_t speedPercent_ = 50;
    uint32_t rotationTimeInMillis_ = 3000;

    bool wasFaultReported_ = false;
    bool timedRotationStarted_ = false;
    uint32_t timedRotationEndTimestamp_ = 0;

    void checkMotorFault();
    void checkTimedRotation();

public:
    SpindleController(
        ILoggerSink& loggerSink,
        ISystemClock& systemClock,
        IMotor& motor
    );

    virtual void tick() override;
    virtual void init(const SpindlePersistentConfig& config) override;

    virtual bool wasFaultReported() override;

    virtual void startRotation() override;
    virtual void startTimedRotation(uint32_t rotationMillis) override;
    virtual void startTimedRotation() override;

    virtual void stopRotation() override;

    virtual bool isTimedRotationFinished() const override;

    virtual void setDirectionClockwise() override;
    virtual void setDirectionCounterClockwise() override;
    virtual bool isDirectionClockwise() const override;

    virtual void setSpeedPercent(uint8_t value) override;
    virtual uint8_t getSpeedPercent() const override;

    virtual void setRotationTimeInMillis(uint32_t value) override;
    virtual uint32_t getRotationTimeInMillis() const override;
};
}
