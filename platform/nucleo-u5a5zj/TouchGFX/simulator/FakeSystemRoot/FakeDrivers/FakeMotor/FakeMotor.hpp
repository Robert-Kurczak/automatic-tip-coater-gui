#pragma once

#include "application/System/Drivers/Logger/ILogger.hpp"
#include "application/System/Drivers/Motor/IMotor.hpp"

#include <string>

namespace ATC {
class FakeMotor : public IMotor {
private:
    const std::string name_;
    ILogger& logger_;

    bool isDirectionClockwise_ = true;

public:
    FakeMotor(std::string&& name, ILogger& logger);

    virtual void init() override;

    virtual void startRotation(uint8_t speedPercent) override;
    virtual void stopRotation() override;

    virtual void setDirectionClockwise() override;
    virtual void setDirectionCounterClockwise() override;
    virtual bool isDirectionClockwise() const override;
};
}