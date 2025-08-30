#pragma once

#include "../../IConsumableTask.hpp"
#include "../AxisTestResults.hpp"

#include "application/System/Drivers/Logger/ILogger.hpp"

namespace ATC {
class ZAxisTestTask : public IConsumableTask<AxisTestResults> {
private:
    ILogger& logger_;

public:
    ZAxisTestTask(ILogger& logger);

    virtual void start() override;
    virtual void reset() override;
    virtual void tick() override;
    virtual bool isFinished() const override;
    virtual AxisTestResults consumeResult() override;
};
}