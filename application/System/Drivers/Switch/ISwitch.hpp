#pragma once

namespace ATC {
class ISwitch {
public:
    ISwitch() = default;
    ISwitch(const ISwitch&) = delete;
    ISwitch& operator=(const ISwitch&) = delete;
    ISwitch(ISwitch&&) = delete;
    ISwitch& operator=(ISwitch&&) = delete;
    virtual ~ISwitch() = default;

    virtual void init() = 0;

    virtual void turnOn() = 0;
    virtual void turnOff() = 0;
};
}