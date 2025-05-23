#include "FlexibleMemoryController.hpp"

FlexibleMemoryController::FlexibleMemoryController(
    const uintptr_t registerAddress_,
    const uintptr_t dataAddress_
) :
    registerAddress {
        reinterpret_cast<volatile uint16_t*>(registerAddress_)
    },
    dataAddress {reinterpret_cast<volatile uint16_t*>(dataAddress_)} {}

void FlexibleMemoryController::writeRegister(const uint16_t value) {
    *registerAddress = value;
}

void FlexibleMemoryController::writeData(const uint16_t value) {
    *dataAddress = value;
}