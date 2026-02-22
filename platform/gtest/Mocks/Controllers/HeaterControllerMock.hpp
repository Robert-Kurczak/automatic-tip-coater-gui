#pragma once

#include "application/System/Controllers/HeaterController/IHeaterController.hpp"

#include "gmock/gmock.h"

using namespace testing;

namespace ATC {
class HeaterControllerMock : public IHeaterController {
public:
    MOCK_METHOD(
        void,
        init,
        (const HeaterPersistentConfig& config),
        (override)
    );

    MOCK_METHOD(void, tick, (), (override));

    MOCK_METHOD(void, turnOn, (), (override));

    MOCK_METHOD(void, turnOff, (), (override));

    MOCK_METHOD(bool, isOn, (), (const override));

    MOCK_METHOD(
        void,
        setTargetTemperatureInCelsius,
        (float value),
        (override)
    );

    MOCK_METHOD(
        float,
        getTargetTemperatureInCelsius,
        (),
        (const override)
    );

    MOCK_METHOD(bool, isAtTargetTemperature, (), (const override));
};
}