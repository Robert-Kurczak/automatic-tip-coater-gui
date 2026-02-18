#pragma once

#include "application/System/Drivers/PersistentStorage/IPersistentStorage.hpp"

#include "gmock/gmock.h"
#include <cstdint>

namespace ATC {
class PersistentStorageMock : public IPersistentStorage {
public:
    MOCK_METHOD(void, init, (), (override));
    MOCK_METHOD(void, read, (uint16_t, std::span<uint8_t>), (override));
    MOCK_METHOD(
        void,
        write,
        (uint16_t address, std::span<uint8_t>),
        (override)
    );
};
}