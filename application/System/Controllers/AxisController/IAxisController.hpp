#pragma once

#include "application/System/Controllers/PersistentStorageController/PersistentData/AxisPersistentConfig.hpp"

#include <cstdint>

namespace ATC {
class IAxisController {
public:
    IAxisController() = default;
    IAxisController(const IAxisController&) = delete;
    IAxisController& operator=(const IAxisController&) = delete;
    IAxisController(IAxisController&&) = delete;
    IAxisController& operator=(IAxisController&&) = delete;
    virtual ~IAxisController() = default;

    virtual void init(const AxisPersistentConfig& config) = 0;
    virtual void tick() = 0;

    [[nodiscard]] virtual bool wasFaultReported() const = 0;

    virtual void moveToPosition(uint32_t position) = 0;
    [[nodiscard]] virtual uint32_t getCurrentPosition() const = 0;

    virtual void moveToMinLimitPosition() = 0;
    [[nodiscard]] virtual bool isAtMinLimitPosition() const = 0;

    virtual void moveToMaxLimitPosition() = 0;
    [[nodiscard]] virtual bool isAtMaxLimitPosition() const = 0;

    virtual void moveToHomePosition() = 0;
    [[nodiscard]] virtual bool isAtHomePosition() const = 0;

    virtual void moveToStartPosition() = 0;
    [[nodiscard]] virtual bool isAtStartPosition() const = 0;

    virtual void moveToEndPosition() = 0;
    [[nodiscard]] virtual bool isAtEndPosition() const = 0;

    virtual void setStartPosition(uint32_t value) = 0;
    [[nodiscard]] virtual uint32_t getStartPosition() const = 0;

    virtual void setEndPosition(uint32_t value) = 0;
    [[nodiscard]] virtual uint32_t getEndPosition() const = 0;

    virtual void setSpeed(uint32_t value) = 0;
    [[nodiscard]] virtual uint32_t getSpeed() const = 0;
};
}