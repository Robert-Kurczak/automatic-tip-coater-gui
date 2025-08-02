#pragma once

#include <span>
#include <stdint.h>

namespace ATC {
class ISpi {
public:
    virtual void sendData(const std::span<const uint8_t>& data) = 0;
    virtual void receiveData(const std::span<uint8_t>& outputBuffer) = 0;
};
}