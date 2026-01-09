#pragma once

#include <cstdint>

namespace ATC {
class IFlexibleMemoryController {
public:
    struct RegisterAddress {
        uintptr_t value;
    };

    struct DataAddress {
        uintptr_t value;
    };

    struct RegisterNumber {
        uint16_t value;
    };

    struct Data {
        uint16_t value;
    };

    struct Instruction {
        RegisterNumber registerNumber;
        Data data;
    };

    IFlexibleMemoryController() = default;
    IFlexibleMemoryController(const IFlexibleMemoryController&) = delete;
    IFlexibleMemoryController& operator=(
        const IFlexibleMemoryController&
    ) = delete;
    IFlexibleMemoryController(IFlexibleMemoryController&&) = delete;
    IFlexibleMemoryController& operator=(IFlexibleMemoryController&&) =
        delete;

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