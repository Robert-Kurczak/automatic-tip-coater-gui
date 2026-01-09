#pragma once

#include <span>

namespace ATC {
class IUart {
public:
    IUart() = default;
    IUart(const IUart&) = delete;
    IUart& operator=(const IUart&) = delete;
    IUart(IUart&&) = delete;
    IUart& operator=(IUart&&) = delete;
    virtual ~IUart() = default;

    virtual void write(const std::span<const char>& data) = 0;
    virtual void read(const std::span<char>& outputBuffer) = 0;
};
}