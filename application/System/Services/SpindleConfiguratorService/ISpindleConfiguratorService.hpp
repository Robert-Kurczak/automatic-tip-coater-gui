#pragma once

#include <cstdint>

namespace ATC {
class ISpindleConfiguratorService {
public:
    ISpindleConfiguratorService() = default;
    ISpindleConfiguratorService(const ISpindleConfiguratorService&) =
        delete;
    ISpindleConfiguratorService& operator=(
        const ISpindleConfiguratorService&
    ) = delete;
    ISpindleConfiguratorService(ISpindleConfiguratorService&&) = delete;
    ISpindleConfiguratorService& operator=(
        ISpindleConfiguratorService&&
    ) = delete;
    virtual ~ISpindleConfiguratorService() = default;

    virtual void resetBufferedConfig() = 0;

    virtual void showcaseRotation() = 0;

    virtual void increaseSpeedPercent() = 0;
    virtual void decreaseSpeedPercent() = 0;
    virtual void saveSpeedPercent() = 0;
    [[nodiscard]] virtual uint8_t getSpeedPercent() const = 0;

    virtual void setDirectionClockwise() = 0;
    virtual void setDirectionCounterClockwise() = 0;
    virtual void saveDirection() = 0;
    [[nodiscard]] virtual bool isDirectionClockwise() const = 0;

    virtual void increaseRotationTimeInMillis() = 0;
    virtual void decreaseRotationTimeInMillis() = 0;
    virtual void saveRotationTimeInMillis() = 0;
    [[nodiscard]] virtual uint32_t getRotationTimeInMillis() const = 0;
};
}