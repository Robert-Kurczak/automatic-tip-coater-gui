#pragma once

#include "FakeDrivers/FakeDisplay/FakeDisplay.hpp"
#include "FakeDrivers/FakeLoggerSink/FakeLoggerSink.hpp"
#include "FakeDrivers/FakeMotor/FakeMotor.hpp"
#include "FakeDrivers/FakePersistentStorage/FakePersistentStorage.hpp"
#include "FakeDrivers/FakeResistiveTouchPanel/FakeResistiveTouchPanel.hpp"
#include "FakeDrivers/FakeSwitch/FakeSwitch.hpp"
#include "FakeDrivers/FakeTemperatureSensor/FakeTemperatureSensor.hpp"
#include "FakePorts/FakeSystemClock/FakeSystemClock.hpp"
#include "application/System/Controllers/AxisController/XAxisController/XAxisController.hpp"
#include "application/System/Controllers/AxisController/YAxisController/YAxisController.hpp"
#include "application/System/Controllers/AxisController/ZAxisController/ZAxisController.hpp"
#include "application/System/Controllers/HeaterController/HysteresisHeaterController/HysteresisHeaterController.hpp"
#include "application/System/Controllers/PersistentStorageController/PersistentStorageController.hpp"
#include "application/System/Controllers/SpindleController/SpindleController.hpp"
#include "application/System/Controllers/TouchPanelController/ResistiveTouchPanelController/ResistiveTouchPanelController.hpp"
#include "application/System/Root/SystemRoot.hpp"
#include "application/System/Tasks/Task/NullTask/NullTask.hpp"
#include "application/System/Tasks/TaskScheduler/SingleTaskScheduler/SingleTaskScheduler.hpp"
#include "application/Utils/Math.hpp"

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

    FakeSwitch fakeSwitch_ {loggerSink_, "Heater switch"};
    FakeTemperatureSensor temperatureSensor_ {
        loggerSink_,
        "TemperatureSensor"
    };
    HysteresisHeaterController heaterController_ {
        loggerSink_,
        fakeSwitch_,
        temperatureSensor_
    };

    FakeDisplay display_ {loggerSink_};

    FakeResistiveTouchPanel resistiveTouchPanel_ {loggerSink_};
    FakeSystemClock systemClock_ {};
    ResistiveTouchPanelController resistiveTouchPanelController_ {
        resistiveTouchPanel_,
        systemClock_,
        ATC::Rectangle {
                        .xStart_ = 0,
                        .xEnd_ = 800,
                        .yStart_ = 0,
                        .yEnd_ = 480
        },
        ATC::Vector2 {.x_ = 800, .y_ = 480},
        3000
    };

    NullTask nullTask_ {};
    SingleTaskScheduler taskScheduler_ {nullTask_};

    SystemComponents targetComponents_ {
        .persistentStorageController = persistentStorageController_,
        .xAxisController = xAxisController_,
        .yAxisController = yAxisController_,
        .zAxisController = zAxisController_,
        .spindleController = spindleController_,
        .heaterController = heaterController_,
        .display = display_,
        .touchPanelController = resistiveTouchPanelController_,
        .taskScheduler = taskScheduler_
    };

    SystemApi systemApi_;

    TargetSystemRoot();

public:
    static TargetSystemRoot& getSystemRoot();
};
}