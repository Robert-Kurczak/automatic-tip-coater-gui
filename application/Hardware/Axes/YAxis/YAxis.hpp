#pragma once

#include "IYAxis.hpp"
#include "application/System/Logger/ILogger.hpp"

#include <functional>
#include <stdint.h>

namespace ATC {
class YAxis : public IYAxis {
private:
    ILogger& logger_;

public:
    YAxis(ILogger& logger);

    virtual void init() override;
    virtual void tick() override;

    virtual void startTestTask(AxisTestTaskCallback callback) override;

    virtual void increaseStartPosition() override;
    virtual void decreaseStartPosition() override;
    virtual void saveStartPosition() override;
    virtual uint32_t getStartPosition() override;

    virtual void increaseEndPosition() override;
    virtual void decreaseEndPosition() override;
    virtual void saveEndPosition() override;
    virtual uint32_t getEndPosition() override;

    virtual void increaseSpeed() override;
    virtual void decreaseSpeed() override;
    virtual void saveSpeed() override;
    virtual uint32_t getSpeed() override;
};
}