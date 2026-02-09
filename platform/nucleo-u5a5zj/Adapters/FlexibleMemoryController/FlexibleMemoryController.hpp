#pragma once

#include "application/System/Ports/IFlexibleMemoryController.hpp"

namespace ATC {
class FlexibleMemoryController : public IFlexibleMemoryController {
private:
    volatile uint16_t* registerRawAddress_;
    volatile uint16_t* dataRawAddress_;

public:
    FlexibleMemoryController(
        RegisterAddress registerAddress,
        DataAddress dataAddress
    );

    void writeRegister(RegisterNumber registerNumber) override;
    void writeData(Data data) override;
    void write(const Instruction& instruction) override;

    [[nodiscard]] uint16_t readData() const override;
    [[nodiscard]] uint16_t read(
        RegisterNumber registerNumber
    ) const override;
};
}