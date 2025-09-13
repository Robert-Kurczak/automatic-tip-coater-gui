#pragma once

#include "../IConsumableTask.hpp"
#include "AxisTestResults.hpp"
#include "application/System/Controllers/AxisController/IAxisController.hpp"
#include "application/System/Ports/ISystemClock.hpp"

#include <array>

namespace ATC {
class AxisTestTask : public IConsumableTask<AxisTestResults> {
private:
    IAxisController& axisController_;
    ISystemClock& systemClock_;
    const uint32_t axisMoveTimeoutInMillis_;

    uint32_t axisMoveStartTimestampInMillis_ = 0;

    TaskState state_ = TaskState::IDLE;

    AxisTestResults testResults_ {
        .startLimitSwitchSuccess = false,
        .endLimitSwitchSuccess = false,
        .motorDriverSuccess = false
    };

    uint8_t currentStage_ = 0;

    void moveAxisToMinLimitPosition();
    void waitForAxisAtMinLimitPosition();

    void moveAxisToMaxLimitPosition();
    void waitForAxisAtMaxLimitPosition();

    void finishTask();

    using stageMethod = void (AxisTestTask::*)();

    static constexpr std::array<stageMethod, 5> stages_ {
        &AxisTestTask::moveAxisToMinLimitPosition,
        &AxisTestTask::waitForAxisAtMinLimitPosition,
        &AxisTestTask::moveAxisToMaxLimitPosition,
        &AxisTestTask::waitForAxisAtMaxLimitPosition,
        &AxisTestTask::finishTask
    };

public:
    AxisTestTask(
        IAxisController& axisController,
        ISystemClock& systemClock,
        uint32_t axisMoveTimeoutInMillis
    );

    virtual void start() override;
    virtual void reset() override;
    virtual void tick() override;
    virtual bool isFinished() const override;
    virtual AxisTestResults consumeResult() override;
};
}