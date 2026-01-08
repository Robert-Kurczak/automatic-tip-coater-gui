#pragma once

#include "application/Utils/TaggedType.hpp"

#include <cstdint>

namespace ATC {
class IFlexibleMemoryController {
private:
    struct RegisterAddressTag {};
    struct DataAddressTag {};

    struct RegisterNumberTag {};
    struct DataTag {};

public:
    using RegisterAddress = TaggedType<RegisterAddressTag, uintptr_t>;
    using DataAddress = TaggedType<DataAddressTag, uintptr_t>;

    using RegisterNumber = TaggedType<RegisterNumberTag, uint16_t>;
    using Data = TaggedType<DataTag, uint16_t>;

    struct Instruction {
        RegisterNumber registerNumber;
        Data data;
    };

    IFlexibleMemoryController() = default;

    IFlexibleMemoryController(const IFlexibleMemoryController&) = delete;

    IFlexibleMemoryController& operator=(
        const IFlexibleMemoryController&
    ) = delete;

    IFlexibleMemoryController(IFlexibleMemoryController&& other) = delete;

    IFlexibleMemoryController& operator=(
        IFlexibleMemoryController&& other
    ) = delete;

    virtual ~IFlexibleMemoryController() = default;

    virtual void writeRegister(RegisterNumber registerNumber) = 0;
    virtual void writeData(Data data) = 0;
    virtual void write(const Instruction& instruction) = 0;

    [[nodiscard]] virtual uint16_t readData() const = 0;
    [[nodiscard]] virtual uint16_t read(
        RegisterNumber registerNumber
    ) const = 0;
};
}