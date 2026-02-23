#pragma once

#include "application/System/Controllers/AxisController/IAxisController.hpp"
#include "application/System/Controllers/AxisController/XAxisController/IXAxisController.hpp"
#include "application/System/Controllers/AxisController/YAxisController/IYAxisController.hpp"
#include "application/System/Controllers/AxisController/ZAxisController/IZAxisController.hpp"

#include "gmock/gmock.h"

using namespace testing;

namespace ATC {
template<typename Base>
class AxisControllerMockBase : public Base {
public:
    MOCK_METHOD(
        void,
        init,
        (const AxisPersistentConfig& config),
        (override)
    );

    MOCK_METHOD(void, tick, (), (override));

    MOCK_METHOD(bool, wasFaultReported, (), (const override));

    MOCK_METHOD(
        void,
        moveToPositionInMicrometers,
        (uint32_t value),
        (override)
    );

    MOCK_METHOD(
        uint32_t,
        getCurrentPositionInMicrometers,
        (),
        (const override)
    );

    MOCK_METHOD(void, moveToMinLimitPosition, (), (override));

    MOCK_METHOD(bool, isAtMinLimitPosition, (), (const override));

    MOCK_METHOD(void, moveToMaxLimitPosition, (), (override));

    MOCK_METHOD(bool, isAtMaxLimitPosition, (), (const override));

    MOCK_METHOD(void, moveToHomePosition, (), (override));

    MOCK_METHOD(bool, isAtHomePosition, (), (const override));

    MOCK_METHOD(void, moveToStartPosition, (), (override));

    MOCK_METHOD(bool, isAtStartPosition, (), (const override));

    MOCK_METHOD(void, moveToEndPosition, (), (override));

    MOCK_METHOD(bool, isAtEndPosition, (), (const override));

    MOCK_METHOD(
        void,
        setStartPositionInMicrometers,
        (uint32_t value),
        (override)
    );

    MOCK_METHOD(
        uint32_t,
        getStartPositionInMicrometers,
        (),
        (const override)
    );

    MOCK_METHOD(
        void,
        setEndPositionInMicrometers,
        (uint32_t value),
        (override)
    );

    MOCK_METHOD(
        uint32_t,
        getEndPositionInMicrometers,
        (),
        (const override)
    );

    MOCK_METHOD(
        void,
        setSpeedInMillimetersPerSecond,
        (uint16_t value),
        (override)
    );

    MOCK_METHOD(
        uint16_t,
        getSpeedInMillimetersPerSecond,
        (),
        (const override)
    );

    MOCK_METHOD(void, cancelMovement, (), (override));
};

class AxisControllerMock :
    public AxisControllerMockBase<IAxisController> {};

class XAxisControllerMock :
    public AxisControllerMockBase<IXAxisController> {
public:
    MOCK_METHOD(void, moveToHeaterFrontPosition, (), (override));

    MOCK_METHOD(bool, isAtHeaterFrontPosition, (), (const override));
};

class YAxisControllerMock :
    public AxisControllerMockBase<IYAxisController> {
public:
    MOCK_METHOD(void, moveToDetectTip, (), (override));

    MOCK_METHOD(bool, isTipDetected, (), (const override));

    MOCK_METHOD(void, moveToCoatingPosition, (), (override));

    MOCK_METHOD(bool, isAtCoatingPosition, (), (const override));
};

class ZAxisControllerMock :
    public AxisControllerMockBase<IZAxisController> {};
}