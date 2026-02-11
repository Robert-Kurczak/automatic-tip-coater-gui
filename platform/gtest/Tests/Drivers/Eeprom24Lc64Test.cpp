#include "application/System/Drivers/PersistentStorage/Eeprom24Lc64/Eeprom24Lc64.hpp"

#include "application/System/Ports/II2c.hpp"
#include "platform/gtest//Mocks/Ports/I2cMock.hpp"
#include "platform/gtest/Matchers/SpanMatcher.hpp"

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <array>

using namespace testing;

namespace ATC {
class Eeprom24Lc64Test : public Test {
public:
    I2cMock i2cMock_ {};
    static constexpr uint8_t DEVICE_ADDRESS = 12;

    Eeprom24Lc64 eeprom24Lc64_ {i2cMock_, DEVICE_ADDRESS};
};

TEST_F(
    Eeprom24Lc64Test,
    GIVEN_eeprom24Lc64_WHEN_readIsCalled_THEN_callIsForwardedToI2c
) {
    constexpr uint16_t address = 5;
    std::array<uint8_t, 3> buffer {0, 1, 2};

    EXPECT_CALL(
        i2cMock_,
        receiveDataFromExternalMemory(
            II2c::DeviceAddress {DEVICE_ADDRESS},
            II2c::MemoryAddress {address},
            II2c::MemoryAddressSize {
                ATC::Eeprom24Lc64::MEMORY_ADDRESS_SIZE
            },
            SpanRefEq(std::span<uint8_t> {buffer})
        )
    );

    eeprom24Lc64_.read(address, buffer);
}

TEST_F(
    Eeprom24Lc64Test,
    GIVEN_eeprom24Lc64_WHEN_writeIsCalled_THEN_callIsForwardedToI2c
) {
    constexpr uint16_t address = 5;
    std::array<uint8_t, 3> buffer {0, 1, 2};

    EXPECT_CALL(
        i2cMock_,
        sendDataToExternalMemory(
            II2c::DeviceAddress {DEVICE_ADDRESS},
            II2c::MemoryAddress {address},
            II2c::MemoryAddressSize {
                ATC::Eeprom24Lc64::MEMORY_ADDRESS_SIZE
            },
            SpanRefEq(std::span<uint8_t> {buffer})
        )
    );

    eeprom24Lc64_.write(address, buffer);
}
}