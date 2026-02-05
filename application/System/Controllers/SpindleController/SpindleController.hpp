#pragma once

#include "ISpindleController.hpp"
#include "application/System/Drivers/LoggerSink/ILoggerSink.hpp"
#include "application/System/Drivers/MotorDriver/IMotorDriver.hpp"
#include "application/System/Ports/ISystemClock.hpp"

#include <cstdint>

namespace ATC {
class SpindleController : public ISpindleController {
private:
    ILoggerSink& loggerSink_;
    ISystemClock& systemClock_;
    IMotorDriver& motorDriver_;

    uint8_t speedPercent_ = 0;
    uint32_t rotationTimeInMillis_ = 0;

    bool wasFaultReported_ = false;
    bool timedRotationStarted_ = false;
    uint32_t timedRotationEndTimestamp_ = 0;

    void checkMotorFault();
    void checkTimedRotation();

public:
    SpindleController(
        ILoggerSink& loggerSink,
        ISystemClock& systemClock,
        IMotorDriver& motorDriver
    );

    void tick() override;
    void init(const SpindlePersistentConfig& config) override;

    [[nodiscard]] bool wasFaultReported() override;

    void startRotation() override;
    void startTimedRotation(uint32_t rotationMillis) override;
    void startTimedRotation() override;

    void stopRotation() override;

    [[nodiscard]] bool isTimedRotationFinished() const override;

    void setDirectionClockwise() override;
    void setDirectionCounterClockwise() override;
    [[nodiscard]] bool isDirectionClockwise() const override;

    void setSpeedPercent(uint8_t value) override;
    [[nodiscard]] uint8_t getSpeedPercent() const override;

    void setRotationTimeInMillis(uint32_t value) override;
    [[nodiscard]] uint32_t getRotationTimeInMillis() const override;
};
}
