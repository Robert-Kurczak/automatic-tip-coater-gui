#include "FakeSystemClock.hpp"

#include <thread>

namespace ATC {
FakeSystemClock::FakeSystemClock() :
    programStartTimePoint_(std::chrono::system_clock::now()) {}

void FakeSystemClock::delayMilliseconds(const uint32_t value) {
    std::this_thread::sleep_for(std::chrono::milliseconds(value));
}

uint32_t FakeSystemClock::getMillisecondsSinceStart() {
    const auto duration =
        std::chrono::system_clock::now() - programStartTimePoint_;

    return std::chrono::duration_cast<std::chrono::milliseconds>(duration)
        .count();
}
}