#pragma once

#include "IFlexibleMemoryController.hpp"

namespace ATC {
class FlexibleMemoryController : public IFlexibleMemoryController {
private:
    volatile uint16_t* registerAddress_;
    volatile uint16_t* dataAddress_;

public:
    FlexibleMemoryController(
        const uintptr_t registerAddress,
        const uintptr_t dataAddress
    );

    virtual void writeRegister(const uint16_t value) override;
    virtual void writeData(const uint16_t value) override;
    virtual void write(const uint16_t reg, const uint16_t data) override;

    virtual uint16_t readData() const override;
    virtual uint16_t read(const uint16_t reg) const override;
};
}