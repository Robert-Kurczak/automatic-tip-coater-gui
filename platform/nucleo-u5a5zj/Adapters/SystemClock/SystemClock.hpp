#pragma once

#include "application/System/Ports/ISystemClock.hpp"

namespace ATC {
class SystemClock : public ISystemClock {
public:
    virtual void delayMilliseconds(const uint32_t value) override;
    virtual uint32_t getMillisecondsSinceStart() override;
};
}
