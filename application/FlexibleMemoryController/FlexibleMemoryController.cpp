#include "FlexibleMemoryController.hpp"

FlexibleMemoryController::FlexibleMemoryController(
    const uintptr_t registerAddress,
    const uintptr_t dataAddress
) :
    registerAddress_ {
        reinterpret_cast<volatile uint16_t*>(registerAddress)
    },
    dataAddress_ {reinterpret_cast<volatile uint16_t*>(dataAddress)} {}

void FlexibleMemoryController::writeRegister(const uint16_t value) {
    *registerAddress_ = value;
}

void FlexibleMemoryController::writeData(const uint16_t value) {
    *dataAddress_ = value;
}

void FlexibleMemoryController::write(
    const uint16_t reg,
    const uint16_t data
) {
    *registerAddress_ = reg;
    *dataAddress_ = data;
}

uint16_t FlexibleMemoryController::readData() const {
    return *dataAddress_;
}

uint16_t FlexibleMemoryController::read(const uint16_t reg) const {
    *registerAddress_ = reg;

    return *dataAddress_;
}