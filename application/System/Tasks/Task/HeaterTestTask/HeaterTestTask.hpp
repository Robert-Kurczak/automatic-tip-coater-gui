#pragma once

#include "../IConsumableTask.hpp"
#include "HeaterTestResults.hpp"
#include "application/System/Controllers/HeaterController/IHeaterController.hpp"
#include "application/System/Drivers/Logger/ILogger.hpp"

namespace ATC {
class HeaterTestTask : public IConsumableTask<HeaterTestResults> {
private:
    ILogger& logger_;
    IHeaterController& heaterController_;

public:
    HeaterTestTask(ILogger& logger, IHeaterController& heaterController);

    virtual void start() override;
    virtual void reset() override;
    virtual void tick() override;
    virtual bool isFinished() const override;
    virtual HeaterTestResults consumeResult() override;
};
}