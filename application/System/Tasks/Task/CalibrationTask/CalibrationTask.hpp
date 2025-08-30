#pragma once

#include "../IConsumableTask.hpp"
#include "application/System/Drivers/Logger/ILogger.hpp"

namespace ATC {
class CalibrationTask : public IConsumableTask<bool> {
private:
    ILogger& logger_;

public:
    CalibrationTask(ILogger& logger);

    virtual void start() override;
    virtual void reset() override;
    virtual void tick() override;
    virtual bool isFinished() const override;
    virtual bool consumeResult() override;
};
}