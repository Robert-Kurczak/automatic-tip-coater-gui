#include "FlexibleMemoryController.hpp"

namespace ATC {
FlexibleMemoryController::FlexibleMemoryController(
    RegisterAddress registerAddress,
    DataAddress dataAddress
) :
    registerAddress_(registerAddress),
    dataAddress_(dataAddress) {}

void FlexibleMemoryController::writeRegister(
    RegisterNumber registerNumber
) {
    *registerAddress_.value = registerNumber.value;
}

void FlexibleMemoryController::writeData(Data data) {
    *dataAddress_.value = data.value;
}

void FlexibleMemoryController::write(
    RegisterNumber registerNumber,
    Data data
) {
    *registerAddress_.value = registerNumber.value;
    *dataAddress_.value = data.value;
}

uint16_t FlexibleMemoryController::readData() const {
    return *dataAddress_.value;
}

uint16_t FlexibleMemoryController::read(
    RegisterNumber registerNumber
) const {
    *registerAddress_.value = registerNumber.value;

    return *dataAddress_.value;
}
}