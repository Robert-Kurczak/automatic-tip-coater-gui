#pragma once

#include "application/System/Ports/ISystemClock.hpp"

#include <chrono>

namespace ATC {
class FakeSystemClock : public ISystemClock {
private:
    const std::chrono::time_point<std::chrono::system_clock>
        programStartTimePoint_;

public:
    FakeSystemClock();

    virtual void delayMiliseconds(const uint32_t value) override;
    virtual uint32_t getMillisecondsSinceStart() override;
};
}