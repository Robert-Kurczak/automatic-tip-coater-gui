#include "FlexibleMemoryController.hpp"

namespace ATC {
FlexibleMemoryController::FlexibleMemoryController(
    RegisterAddress registerAddress,
    DataAddress dataAddress
) :
    registerRawAddress_ {
        reinterpret_cast<decltype(registerRawAddress_)>( // NOLINT
            registerAddress.value
        )
    },
    dataRawAddress_ {
        reinterpret_cast<decltype(dataRawAddress_)>( // NOLINT
            dataAddress.value
        )
    } {}

void FlexibleMemoryController::writeRegister(
    RegisterNumber registerNumber
) {
    *registerRawAddress_ = registerNumber.value;
}

void FlexibleMemoryController::writeData(Data data) {
    *dataRawAddress_ = data.value;
}

void FlexibleMemoryController::write(const Instruction& instruction) {
    *registerRawAddress_ = instruction.registerNumber.value;
    *dataRawAddress_ = instruction.data.value;
}

uint16_t FlexibleMemoryController::readData() const {
    return *dataRawAddress_;
}

uint16_t FlexibleMemoryController::read(
    RegisterNumber registerNumber
) const {
    *registerRawAddress_ = registerNumber.value;

    return *dataRawAddress_;
}
}