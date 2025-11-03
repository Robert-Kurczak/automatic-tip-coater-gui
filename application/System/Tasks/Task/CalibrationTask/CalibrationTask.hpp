#pragma once

#include "../IConsumableTask.hpp"
#include "application/System/Controllers/AxisController/XAxisController/XAxisController.hpp"
#include "application/System/Controllers/AxisController/YAxisController/YAxisController.hpp"
#include "application/System/Controllers/AxisController/ZAxisController/ZAxisController.hpp"

#include <array>

namespace ATC {
class CalibrationTask : public IConsumableTask<bool> {
private:
    IXAxisController& xAxisController_;
    IYAxisController& yAxisController_;
    IZAxisController& zAxisController_;

    TaskState state_ = TaskState::IDLE;
    bool wasSuccessful_ = false;
    uint8_t currentStage_ = 0;

    void moveAxesToHomePosition();
    void waitForAxesAtHomePosition();

    void moveAxesToStartPosition();
    void waitForAxesAtStartPosition();

    void finishTask();

    using stageMethod = void (CalibrationTask::*)();
    static const std::array<stageMethod, 5> stages_;

public:
    CalibrationTask(
        IXAxisController& xAxisController,
        IYAxisController& yAxisController,
        IZAxisController& zAxisController
    );

    virtual void start() override;
    virtual void reset() override;
    virtual void tick() override;
    virtual bool isFinished() const override;
    virtual bool consumeResult() override;
};
}