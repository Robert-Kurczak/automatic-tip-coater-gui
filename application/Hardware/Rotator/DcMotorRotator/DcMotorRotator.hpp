#pragma once

#include "../IRotator.hpp"
#include "application/System/Logger/ILogger.hpp"

namespace ATC {
class DcMotorRotator : public IRotator {
private:
    ILogger& logger_;

public:
    DcMotorRotator(ILogger& logger);

    virtual void init() override;
    virtual void tick() override;

    virtual void startTestTask(RotatorTestTaskCallback callback) override;

    virtual void increaseSpeed() override;
    virtual void decreaseSpeed() override;
    virtual void saveSpeed() override;
    virtual uint32_t getSpeed() override;

    virtual void setDirectionClockwise() override;
    virtual void setDirectionCounterClockwise() override;
    virtual void saveDirection() override;
    virtual bool isDirectionClockwise() override;

    virtual void increaseRotationTime() override;
    virtual void decreaseRotationTime() override;
    virtual void saveRotationTime() override;
    virtual uint32_t getRotationTime() override;
};
}