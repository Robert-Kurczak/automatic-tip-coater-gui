#pragma once

#include "application/System/Ports/ISpi.hpp"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

using namespace testing;

namespace ATC {
class SpiMock : public ISpi {
public:
    MOCK_METHOD(
        void,
        sendData,
        (const std::span<const uint8_t>&),
        (override)
    );

    MOCK_METHOD(
        void,
        receiveData,
        (const std::span<uint8_t>&),
        (override)
    );

    MOCK_METHOD(
        void,
        sendAndReceiveData,
        (const std::span<const uint8_t>&, const std::span<uint8_t>&),
        (override)
    );

    MOCK_METHOD(uint32_t, getSpeedInKilohertz, (), (const override));
};
}