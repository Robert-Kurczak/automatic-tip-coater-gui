#pragma once

#include <cstdint>

namespace ATC {
class IAdc {
public:
    IAdc() = default;
    IAdc(const IAdc&) = delete;
    IAdc& operator=(const IAdc&) = delete;
    IAdc(IAdc&&) = delete;
    IAdc& operator=(IAdc&&) = delete;
    virtual ~IAdc() = default;

    virtual void init() = 0;

    [[nodiscard]] virtual uint8_t getResolutionBits() const = 0;
    [[nodiscard]] virtual float getReferenceVoltage() const = 0;

    virtual uint32_t readRaw() = 0;
};
};