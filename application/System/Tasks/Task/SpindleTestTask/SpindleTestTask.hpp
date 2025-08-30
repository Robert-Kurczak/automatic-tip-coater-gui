#pragma once

#include "../IConsumableTask.hpp"
#include "SpindleTestResults.hpp"
#include "application/System/Controllers/SpindleController/ISpindleController.hpp"
#include "application/System/Drivers/Logger/ILogger.hpp"

namespace ATC {
class SpindleTestTask : public IConsumableTask<SpindleTestResults> {
private:
    ILogger& logger_;
    ISpindleController& spindleController_;

public:
    SpindleTestTask(
        ILogger& logger_,
        ISpindleController& spindleController
    );

    virtual void start() override;
    virtual void reset() override;
    virtual void tick() override;
    virtual bool isFinished() const override;
    virtual SpindleTestResults consumeResult() override;
};
}
