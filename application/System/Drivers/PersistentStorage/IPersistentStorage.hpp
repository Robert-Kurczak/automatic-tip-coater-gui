#pragma once

#include <cstdint>
#include <span>

namespace ATC {
class IPersistentStorage {
public:
    IPersistentStorage() = default;
    IPersistentStorage(const IPersistentStorage&) = delete;
    IPersistentStorage& operator=(const IPersistentStorage&) = delete;
    IPersistentStorage(IPersistentStorage&&) = delete;
    IPersistentStorage& operator=(IPersistentStorage&&) = delete;
    virtual ~IPersistentStorage() = default;

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