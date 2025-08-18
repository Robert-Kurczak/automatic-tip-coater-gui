#pragma once

#include <stdint.h>

namespace ATC {
class ITemperatureSensor {
public:
    virtual ~ITemperatureSensor() = default;

    virtual void init() = 0;

    virtual uint32_t getCelsius() = 0;
};
}