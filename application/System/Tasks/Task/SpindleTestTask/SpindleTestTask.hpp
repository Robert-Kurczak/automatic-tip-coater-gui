#pragma once

#include "../IConsumableTask.hpp"
#include "SpindleTestResults.hpp"
#include "application/System/Controllers/SpindleController/ISpindleController.hpp"
#include "application/System/Ports/ISystemClock.hpp"

#include <array>

namespace ATC {
class SpindleTestTask : public IConsumableTask<SpindleTestResults> {
private:
    ISpindleController& spindleController_;
    const uint32_t rotationDurationInMillis_;

    TaskState state_ = TaskState::IDLE;
    SpindleTestResults testResults_ {.motorDriverSuccess = false};

    uint8_t currentStage_ = 0;

    void startSpindle();
    void waitForRotationToFinish();

    void finishTask();

    using stageMethod = void (SpindleTestTask::*)();
    static const std::array<stageMethod, 3> stages_;

public:
    SpindleTestTask(
        ISpindleController& spindleController,
        uint32_t rotationDurationInMillis
    );

    virtual void start() override;
    virtual void reset() override;
    virtual void tick() override;
    virtual bool isFinished() const override;
    virtual SpindleTestResults consumeResult() override;
};
}
