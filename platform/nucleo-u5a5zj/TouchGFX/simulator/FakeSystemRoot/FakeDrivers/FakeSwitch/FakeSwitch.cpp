#include "FakeSwitch.hpp"

#include "application/Utils/Logger.hpp"

namespace ATC {
FakeSwitch::FakeSwitch(ILoggerSink& loggerSink, std::string&& name) :
    loggerSink_(loggerSink),
    name_(name) {}

void FakeSwitch::init() {
    log(loggerSink_, LogLevel::Debug, "%s initialized", name_);
}

void FakeSwitch::turnOn() {
    log(loggerSink_, LogLevel::Debug, "%s turned on", name_);
}

void FakeSwitch::turnOff() {
    log(loggerSink_, LogLevel::Debug, "%s turned off", name_);
}

}