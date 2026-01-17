#pragma once

namespace ATC {
class IStepperDriver {
public:
    IStepperDriver() = default;
    IStepperDriver(const IStepperDriver&) = delete;
    IStepperDriver& operator=(const IStepperDriver&) = delete;
    IStepperDriver(IStepperDriver&&) = delete;
    IStepperDriver& operator=(IStepperDriver&&) = delete;
    virtual ~IStepperDriver() = default;

    virtual void init() = 0;

    virtual void start() = 0;
    virtual void stop() = 0;

    virtual void setDirectionClockwise() = 0;
    virtual void setDirectionCounterClockwise() = 0;

    [[nodiscard]] virtual bool isFaultDetected() const = 0;
};
}