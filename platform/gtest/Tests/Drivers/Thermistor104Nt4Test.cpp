
#include "application/System/Drivers/TemperatureSensor/Thermistor104Nt4/Thermistor104Nt4.hpp"

#include "application/System/Drivers/TemperatureSensor/Thermistor104Nt4/Thermistor104Nt4Table.hpp"
#include "platform/gtest/Mocks/Controllers/LoggerSinkMock.hpp"
#include "platform/gtest/Mocks/Ports/AdcMock.hpp"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

using namespace testing;

namespace ATC {
class Thermistor104Nt4Test : public Test {
public:
    LoggerSinkMock loggerSinkMock_ {};
    AdcMock adcMock_ {};

    Thermistor104Nt4 thermistor104Nt4_ {loggerSinkMock_, adcMock_};
};

TEST_F(
    Thermistor104Nt4Test,
    GIVEN_thermistor104Nt4_WHEN_thermistorIsInitialized_THEN_adcIsSetUp
) {
    EXPECT_CALL(adcMock_, init());

    thermistor104Nt4_.init();
}

TEST_F(
    Thermistor104Nt4Test,
    GIVEN_thermistor104Nt4_WHEN_getCelsiusIsCalled_THEN_lookupTableValueIsReturned
) {
    constexpr uint16_t rawValue1 = 200;
    constexpr uint16_t rawValue2 = 500;
    constexpr uint16_t rawValue3 = 900;

    EXPECT_CALL(adcMock_, readRaw())
        .WillOnce(Return(rawValue1))
        .WillOnce(Return(rawValue2))
        .WillOnce(Return(rawValue3));

    ASSERT_EQ(thermistor104Nt4_.getCelsius(), THERMISTOR_104NT4_TABLE[rawValue1]);
    ASSERT_EQ(thermistor104Nt4_.getCelsius(), THERMISTOR_104NT4_TABLE[rawValue2]);
    ASSERT_EQ(thermistor104Nt4_.getCelsius(), THERMISTOR_104NT4_TABLE[rawValue3]);
}
}