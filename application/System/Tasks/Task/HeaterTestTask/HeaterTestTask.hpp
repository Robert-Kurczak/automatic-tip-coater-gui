#pragma once

#include "../IConsumableTask.hpp"
#include "HeaterTestResults.hpp"
#include "application/System/Controllers/HeaterController/IHeaterController.hpp"
#include "application/System/Ports/ISystemClock.hpp"

#include <array>

namespace ATC {
class HeaterTestTask : public IConsumableTask<HeaterTestResults> {
private:
    IHeaterController& heaterController_;
    ISystemClock& systemClock_;
    const uint32_t heatingTimeoutInMillis_;

    uint32_t heatingStartTimestampInMillis_ = 0;

    TaskState state_ = TaskState::IDLE;
    HeaterTestResults testResults_ {.temperatureSuccess = false};
    uint8_t currentStage_ = 0;

    void turnHeaterOn();
    void waitForTargetTemperature();

    void finishTask();

    using stageMethod = void (HeaterTestTask::*)();
    static const std::array<stageMethod, 3> stages_;

public:
    HeaterTestTask(
        IHeaterController& heaterController,
        ISystemClock& systemClock,
        uint32_t heatingTimeoutInMillis
    );

    void start() override;
    void reset() override;
    void tick() override;
    [[nodiscard]] bool isFinished() const override;
    HeaterTestResults consumeResult() override;
};
}