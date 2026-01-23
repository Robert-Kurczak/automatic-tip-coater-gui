#pragma once

#include "application/System/Drivers/LoggerSink/ILoggerSink.hpp"
#include "application/System/Drivers/OutputSwitch/IOutputSwitch.hpp"

#include <string>

namespace ATC {
class FakeSwitch : public IOutputSwitch {
private:
    ILoggerSink& loggerSink_;
    std::string name_;

public:
    FakeSwitch(ILoggerSink& loggerSink, std::string&& name);

    virtual void init() override;

    virtual void turnOn() override;
    virtual void turnOff() override;
};
}