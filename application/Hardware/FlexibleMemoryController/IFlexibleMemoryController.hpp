#pragma once

#include <stdint.h>

namespace ATC {
class IFlexibleMemoryController {
public:
    virtual void writeRegister(const uint16_t value) = 0;
    virtual void writeData(const uint16_t value) = 0;
    virtual void write(const uint16_t reg, const uint16_t data) = 0;

    virtual uint16_t readData() const = 0;
    virtual uint16_t read(const uint16_t reg) const = 0;
};
}