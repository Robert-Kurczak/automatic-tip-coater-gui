#pragma once

#include "application/System/Controllers/PersistentStorageController/PersistentData/SpindlePersistentConfig.hpp"

#include <cstdint>

namespace ATC {
class ISpindleController {
public:
    ISpindleController() = default;
    ISpindleController(const ISpindleController&) = delete;
    ISpindleController& operator=(const ISpindleController&) = delete;
    ISpindleController(ISpindleController&&) = delete;
    ISpindleController& operator=(ISpindleController&&) = delete;
    virtual ~ISpindleController() = default;

    virtual void init(const SpindlePersistentConfig& config) = 0;
    virtual void tick() = 0;

    [[nodiscard]] virtual bool wasFaultReported() = 0;

    virtual void startRotation() = 0;

    virtual void startTimedRotation(uint32_t rotationMillis) = 0;
    virtual void startTimedRotation() = 0;

    virtual void stopRotation() = 0;

    [[nodiscard]] virtual bool isTimedRotationFinished() const = 0;

    virtual void setDirectionClockwise() = 0;
    virtual void setDirectionCounterClockwise() = 0;
    [[nodiscard]] virtual bool isDirectionClockwise() const = 0;

    virtual void setSpeedPercent(uint8_t value) = 0;
    [[nodiscard]] virtual uint8_t getSpeedPercent() const = 0;

    virtual void setRotationTimeInMillis(uint32_t value) = 0;
    [[nodiscard]] virtual uint32_t getRotationTimeInMillis() const = 0;
};
}