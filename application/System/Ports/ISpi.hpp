#pragma once

#include <cstdint>
#include <span>

namespace ATC {
class ISpi {
public:
    ISpi() = default;
    ISpi(const ISpi&) = delete;
    ISpi& operator=(const ISpi&) = delete;
    ISpi(ISpi&&) = delete;
    ISpi& operator=(ISpi&&) = delete;
    virtual ~ISpi() = default;

    virtual void sendData(const std::span<const uint8_t>& data) = 0;
    virtual void receiveData(const std::span<uint8_t>& outputBuffer) = 0;
    virtual void sendAndReceiveData(
        const std::span<const uint8_t>& data,
        const std::span<uint8_t>& outputBuffer
    ) = 0;

    [[nodiscard]] virtual uint32_t getSpeedInKilohertz() const = 0;
};
}