#pragma once

#include <span>
#include <stdint.h>

namespace ATC {
class IUart {
public:
    virtual void write(const std::span<const char>& data) = 0;
    virtual void read(const std::span<char>& outputBuffer) = 0;
};
}