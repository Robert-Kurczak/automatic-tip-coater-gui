#pragma once

#include "application/System/Drivers/LimitSwitch/ILimitSwitch.hpp"
#include "application/System/Drivers/LoggerSink/ILoggerSink.hpp"

#include <string>

namespace ATC {
class FakeLimitSwitch : public ILimitSwitch {
private:
    ILoggerSink& loggerSink_;
    std::string name_;

public:
    FakeLimitSwitch(ILoggerSink& loggerSink, std::string&& name);

    virtual void init() override;

    [[nodiscard]] bool isActive() const override;
};
}