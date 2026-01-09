#pragma once

#include "../IConsumableTask.hpp"
#include "SpindleTestResults.hpp"
#include "application/System/Controllers/SpindleController/ISpindleController.hpp"

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

    void start() override;
    void reset() override;
    void tick() override;
    [[nodiscard]] bool isFinished() const override;
    SpindleTestResults consumeResult() override;
};
}
