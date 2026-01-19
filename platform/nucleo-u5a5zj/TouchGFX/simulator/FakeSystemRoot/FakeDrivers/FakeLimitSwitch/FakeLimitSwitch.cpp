#include "FakeLimitSwitch.hpp"

#include "application/Utils/Logger.hpp"

namespace ATC {
FakeLimitSwitch::FakeLimitSwitch(
    ILoggerSink& loggerSink,
    std::string&& name
) :
    loggerSink_(loggerSink),
    name_(name) {}

void FakeLimitSwitch::init() {
    log(loggerSink_, LogLevel::Debug, "{} initialized", name_);
}

bool FakeLimitSwitch::isActive() const {
    return false;
}

}