#pragma once

namespace ATC {
class IOutputSwitch {
public:
    IOutputSwitch() = default;
    IOutputSwitch(const IOutputSwitch&) = delete;
    IOutputSwitch& operator=(const IOutputSwitch&) = delete;
    IOutputSwitch(IOutputSwitch&&) = delete;
    IOutputSwitch& operator=(IOutputSwitch&&) = delete;
    virtual ~IOutputSwitch() = default;

    virtual void init() = 0;

    virtual void turnOn() = 0;
    virtual void turnOff() = 0;
};
}