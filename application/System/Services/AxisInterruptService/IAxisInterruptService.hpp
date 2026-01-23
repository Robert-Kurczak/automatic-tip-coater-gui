#pragma once

namespace ATC {
class IAxisInterruptService {
public:
    IAxisInterruptService() = default;
    IAxisInterruptService(const IAxisInterruptService&) = delete;
    IAxisInterruptService& operator=(const IAxisInterruptService&) =
        delete;
    IAxisInterruptService(IAxisInterruptService&&) = delete;
    IAxisInterruptService& operator=(IAxisInterruptService&&) = delete;
    virtual ~IAxisInterruptService() = default;

    virtual void handleStepInterrupt() = 0;
    virtual void handleMinLimitReachedInterrupt() = 0;
    virtual void handleMaxLimitReachedInterrupt() = 0;
};
}