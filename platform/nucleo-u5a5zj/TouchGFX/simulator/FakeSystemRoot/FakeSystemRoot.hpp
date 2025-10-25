#pragma once

#include "FakeDrivers/FakeLoggerSink/FakeLoggerSink.hpp"
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
    FakeLoggerSink loggerSink_ {};
    FakePersistentStorage persistentStorage_ {
        loggerSink_,
        "atc-storage.bin",
        4096
    };
    PersistentStorageController persistentStorageController_ {
        persistentStorage_
    };

    XAxisController xAxisController_ {loggerSink_};
    YAxisController yAxisController_ {loggerSink_};
    ZAxisController zAxisController_ {loggerSink_};

    FakeMotor spindleMotor_ {loggerSink_, "Spindle Motor"};
    SpindleController spindleController_ {loggerSink_, spindleMotor_};

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