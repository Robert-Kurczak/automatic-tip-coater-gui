#pragma once

#include "../IConsumableTask.hpp"
#include "application/System/Controllers/AxisController/XAxisController/IXAxisController.hpp"
#include "application/System/Controllers/AxisController/YAxisController/IYAxisController.hpp"
#include "application/System/Controllers/AxisController/ZAxisController/IZAxisController.hpp"

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

    void start() override;
    void reset() override;
    void tick() override;
    [[nodiscard]] bool isFinished() const override;
    bool consumeResult() override;
};
}