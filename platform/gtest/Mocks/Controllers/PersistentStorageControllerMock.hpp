#pragma once

#include "application/System/Controllers/PersistentStorageController/IPersistentStorageController.hpp"

#include "gmock/gmock.h"

namespace ATC {
class PersistentStorageControllerMock :
    public IPersistentStorageController {
public:
    MOCK_METHOD(void, init, (), (override));

    MOCK_METHOD(
        void,
        saveXAxisConfig,
        (const AxisPersistentConfig& config),
        (override)
    );

    MOCK_METHOD(
        void,
        saveYAxisConfig,
        (const AxisPersistentConfig& config),
        (override)
    );

    MOCK_METHOD(
        void,
        saveZAxisConfig,
        (const AxisPersistentConfig& config),
        (override)
    );

    MOCK_METHOD(
        void,
        saveSpindleConfig,
        (const SpindlePersistentConfig& config),
        (override)
    );

    MOCK_METHOD(
        void,
        saveHeaterConfig,
        (const HeaterPersistentConfig& config),
        (override)
    );

    MOCK_METHOD(AxisPersistentConfig, loadXAxisConfig, (), (override));

    MOCK_METHOD(AxisPersistentConfig, loadYAxisConfig, (), (override));

    MOCK_METHOD(AxisPersistentConfig, loadZAxisConfig, (), (override));

    MOCK_METHOD(
        SpindlePersistentConfig,
        loadSpindleConfig,
        (),
        (override)
    );

    MOCK_METHOD(HeaterPersistentConfig, loadHeaterConfig, (), (override));
};
}