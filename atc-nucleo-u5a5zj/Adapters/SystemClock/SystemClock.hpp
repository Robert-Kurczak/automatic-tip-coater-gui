#pragma once

#include "application/Ports/ISystemClock.hpp"

namespace ATC {
class SystemClock : public ISystemClock {
public:
    virtual void delayMiliseconds(const uint32_t value) override;
    virtual uint32_t getMillisecondsSinceStart() override;
};
}