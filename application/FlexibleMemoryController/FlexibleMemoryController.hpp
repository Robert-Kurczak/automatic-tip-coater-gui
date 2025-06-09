#pragma once

#include <stdint.h>

class FlexibleMemoryController {
private:
    volatile uint16_t* registerAddress_;
    volatile uint16_t* dataAddress_;

public:
    FlexibleMemoryController(
        const uintptr_t registerAddress,
        const uintptr_t dataAddress
    );

    void writeRegister(const uint16_t value);
    void writeData(const uint16_t value);
    void write(const uint16_t reg, const uint16_t data);

    uint16_t readData() const;
    uint16_t read(const uint16_t reg) const;
};