#pragma once

#include "FakeDrivers/FakeLogger/FakeLogger.hpp"
#include "FakeDrivers/FakeMotor/FakeMotor.hpp"
#include "FakeDrivers/FakePersistentStorage/FakePersistentStorage.hpp"
#include "application/System/Controllers/AxisController/XAxisController/XAxisController.hpp"
#include "application/System/Controllers/AxisController/YAxisController/YAxisController.hpp"
#include "application/System/Controllers/AxisController/ZAxisController/ZAxisController.hpp"
#include "application/System/Controllers/PersistentStorageController/PersistentStorageController.hpp"
#include "application/System/Controllers/SpindleController/SpindleController.hpp"
#include "application/System/Root/SystemRoot.hpp"

namespace ATC {
class TargetSystemRoot : public SystemRoot {
private:
    FakeLogger logger_ {};
    FakePersistentStorage persistentStorage_ {
        logger_,
        "atc-storage.bin",
        4096
    };
    PersistentStorageController persistentStorageController_ {
        persistentStorage_
    };

    XAxisController xAxisController_ {logger_};
    YAxisController yAxisController_ {logger_};
    ZAxisController zAxisController_ {logger_};

    FakeMotor spindleMotor_ {"Spindle Motor", logger_};
    SpindleController spindleController_ {logger_, spindleMotor_};

    SystemComponents targetComponents_ {
        .persistentStorageController = persistentStorageController_,
        .xAxisController = xAxisController_,
        .yAxisController = yAxisController_,
        .zAxisController = zAxisController_,
        .spindleController = spindleController_,
    };

    SystemApi systemApi_;

    TargetSystemRoot();

public:
    static TargetSystemRoot& getSystemRoot();
};
}