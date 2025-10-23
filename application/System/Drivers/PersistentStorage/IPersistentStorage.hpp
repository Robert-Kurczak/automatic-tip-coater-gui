#pragma once

#include <span>
#include <stdint.h>

namespace ATC {
class IPersistentStorage {
public:
    virtual void init() = 0;

    virtual void read(
        uint32_t address,
        const std::span<uint8_t>& outputBuffer
    ) = 0;

    virtual void write(
        uint32_t address,
        const std::span<const uint8_t>& data
    ) = 0;
};
}