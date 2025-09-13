#pragma once

#include "../IConsumableTask.hpp"
#include "HeaterTestResults.hpp"
#include "application/System/Controllers/HeaterController/IHeaterController.hpp"
#include "application/System/Ports/ISystemClock.hpp"

namespace ATC {
class HeaterTestTask : public IConsumableTask<HeaterTestResults> {
private:
    IHeaterController& heaterController_;
    ISystemClock& systemClock_;
    const uint32_t heatingTimeoutInMillis_;

    uint32_t heatingStartTimestampInMillis_;

    TaskState state_ = TaskState::IDLE;
    HeaterTestResults testResults_ {.temperatureSuccess = false};
    uint8_t currentStage_ = 0;

    void turnHeaterOn();
    void waitForTargetTemperature();

    void finishTask();

    using stageMethod = void (HeaterTestTask::*)();

    static constexpr std::array<stageMethod, 3> stages_ {
        &HeaterTestTask::turnHeaterOn,
        &HeaterTestTask::waitForTargetTemperature,
        &HeaterTestTask::finishTask
    };

public:
    HeaterTestTask(
        IHeaterController& heaterController,
        ISystemClock& systemClock,
        uint32_t heatingTimeoutInMillis
    );

    virtual void start() override;
    virtual void reset() override;
    virtual void tick() override;
    virtual bool isFinished() const override;
    virtual HeaterTestResults consumeResult() override;
};
}