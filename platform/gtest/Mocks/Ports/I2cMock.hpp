#pragma once

#include "application/System/Ports/II2c.hpp"

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <span>

using namespace testing;

namespace ATC {
class I2cMock : public II2c {
public:
    MOCK_METHOD(
        void,
        sendData,
        (DeviceAddress, std::span<uint8_t>),
        (const override)
    );

    MOCK_METHOD(
        void,
        sendDataToExternalMemory,
        (DeviceAddress,
         MemoryAddress,
         MemoryAddressSize,
         std::span<uint8_t>),
        (override)
    );

    MOCK_METHOD(
        void,
        receiveData,
        (DeviceAddress, std::span<uint8_t>),
        (override)
    );

    MOCK_METHOD(
        void,
        receiveDataFromExternalMemory,
        (DeviceAddress,
         MemoryAddress,
         MemoryAddressSize,
         std::span<uint8_t>),
        (override)
    );
};
}