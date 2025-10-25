#pragma once

#include "application/System/Drivers/LoggerSink/ILoggerSink.hpp"

namespace ATC {
class FakeLoggerSink : public ILoggerSink {
public:
    virtual ILoggerSink& operator<<(std::string_view text) override;
};
}