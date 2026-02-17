#pragma once

#include "application/System/Drivers/TemperatureSensor/ITemperatureSensor.hpp"
#include "gmock/gmock.h"
namespace ATC {
class TemperatureSensorMock : public ITemperatureSensor {
public:
    MOCK_METHOD(void, init, (), (override));
    MOCK_METHOD(float, getCelsius, (), (override));
};
}