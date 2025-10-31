#pragma once

#include "../IConsumableTask.hpp"
#include "AxisTestResults.hpp"
#include "application/System/Controllers/AxisController/IAxisController.hpp"
#include "application/System/Ports/ISystemClock.hpp"

#include <array>

namespace ATC {
class AxisTestTask : public IConsumableTask<AxisTestResults> {
private:
    IConsumableTask<bool>& calibrationTask_;
    IAxisController& axisController_;
    ISystemClock& systemClock_;
    const uint32_t axisMoveTimeoutInMillis_;

    TaskState state_ = TaskState::IDLE;
    uint32_t axisMoveStartTimestampInMillis_ = 0;
    AxisTestResults testResults_ {
        .startLimitSwitchSuccess = false,
        .endLimitSwitchSuccess = false,
        .motorDriverSuccess = false
    };

    uint8_t currentStage_ = 0;

    void calibrateAxes();
    void waitForCalibrationFinish();

    void moveAxisToMinLimitPosition();
    void waitForAxisAtMinLimitPosition();

    void moveAxisToMaxLimitPosition();
    void waitForAxisAtMaxLimitPosition();

    void finishTask();

    using stageMethod = void (AxisTestTask::*)();
    static const std::array<stageMethod, 7> stages_;

public:
    AxisTestTask(
        IConsumableTask<bool>& calibrationTask,
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