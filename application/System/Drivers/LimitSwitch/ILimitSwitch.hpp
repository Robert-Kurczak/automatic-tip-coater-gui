#pragma once

namespace ATC {
class ILimitSwitch {
public:
    ILimitSwitch() = default;
    ILimitSwitch(const ILimitSwitch&) = delete;
    ILimitSwitch& operator=(const ILimitSwitch&) = delete;
    ILimitSwitch(ILimitSwitch&&) = delete;
    ILimitSwitch& operator=(ILimitSwitch&&) = delete;
    virtual ~ILimitSwitch() = default;

    virtual void init() = 0;

    [[nodiscard]] virtual bool isActive() const = 0;
};
}