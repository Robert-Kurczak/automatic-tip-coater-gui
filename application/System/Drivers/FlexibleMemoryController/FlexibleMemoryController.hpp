#pragma once

#include "IFlexibleMemoryController.hpp"

namespace ATC {
class FlexibleMemoryController : public IFlexibleMemoryController {
private:
    RegisterAddress registerAddress_;
    DataAddress dataAddress_;

public:
    FlexibleMemoryController(
        RegisterAddress registerAddress,
        DataAddress dataAddress
    );

    void writeRegister(RegisterNumber registerNumber) override;
    void writeData(Data data) override;
    void write(RegisterNumber registerNumber, Data data) override;

    [[nodiscard]] uint16_t readData() const override;
    [[nodiscard]] uint16_t read(
        RegisterNumber registerNumber
    ) const override;
};
}