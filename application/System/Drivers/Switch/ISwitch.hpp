#pragma once

namespace ATC {
class ISwitch {
public:
    virtual ~ISwitch() = default;

    virtual void init() = 0;

    virtual void turnOn() = 0;
    virtual void turnOff() = 0;
};
}