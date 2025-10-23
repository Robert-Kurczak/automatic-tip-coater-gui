#include "FakeMotor.hpp"

namespace ATC {
FakeMotor::FakeMotor(std::string&& name, ILogger& logger) :
    name_(std::move(name)),
    logger_(logger) {}

void FakeMotor::init() {
    logger_.log(LOG_LEVEL::DEBUG_LOG, [&]() {
        return name_ + "initialized";
    });
}

void FakeMotor::startRotation(uint8_t speedPercent) {
    logger_.log(LOG_LEVEL::DEBUG_LOG, [&]() {
        return name_ + "started";
    });
}
void FakeMotor::stopRotation() {
    logger_.log(LOG_LEVEL::DEBUG_LOG, [&]() {
        return name_ + "stopped";
    });
}

void FakeMotor::setDirectionClockwise() {
    isDirectionClockwise_ = true;

    logger_.log(LOG_LEVEL::DEBUG_LOG, [&]() {
        return "Clockwise direction set for" + name_;
    });
}

void FakeMotor::setDirectionCounterClockwise() {
    isDirectionClockwise_ = false;

    logger_.log(LOG_LEVEL::DEBUG_LOG, [&]() {
        return "Counter clockwise direction set for" + name_;
    });
}

bool FakeMotor::isDirectionClockwise() const {
    return isDirectionClockwise_;
}
}