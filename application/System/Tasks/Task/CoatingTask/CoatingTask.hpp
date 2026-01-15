#pragma once

#include "../IConsumableTask.hpp"
#include "application/System/Controllers/AxisController/XAxisController/IXAxisController.hpp"
#include "application/System/Controllers/AxisController/YAxisController/IYAxisController.hpp"
#include "application/System/Controllers/AxisController/ZAxisController/IZAxisController.hpp"
#include "application/System/Controllers/HeaterController/IHeaterController.hpp"
#include "application/System/Controllers/SpindleController/ISpindleController.hpp"

#include <array>

namespace ATC {
class CoatingTask : public IConsumableTask<bool> {
private:
    IConsumableTask<bool>& calibrationTask_;
    IXAxisController& xAxisController_;
    IYAxisController& yAxisController_;
    IZAxisController& zAxisController_;
    ISpindleController& spindleController_;
    IHeaterController& heaterController_;

    TaskState state_ = TaskState::IDLE;
    bool wasSuccessful_ = false;
    uint8_t currentStage_ = 0;

    void calibrateAxes();
    void waitForCalibrationFinish();

    void startHeater();

    void moveAxesToInitialPosition();
    void waitForAxesAtInitialPosition();

    void moveZAxisToEndPosition();
    void waitForZAxisAtEndPosition();

    void detectTipWithYAxis();
    void waitForTipDetection();

    void moveYAxisToCoatingPosition();
    void waitForYAxisAtCoatingPosition();

    void moveZAxisToStartPosition();
    void waitForZAxisAtStartPosition();

    void moveXAxisToEndPosition();
    void waitForXAxisAtEndPosition();

    void waitForHeaterTemperature();

    void startRotation();

    void moveXAxisToHeaterFrontPosition();
    void waitForXAxisAtHeaterFrontPosition();

    void startTimedRotationInHeaterFront();
    void waitForTimedRotationToFinish();

    void moveXAxisToStartPosition();
    void waitForXAxisAtStartPosition();

    void stopRotation();

    void stopHeater();

    void finishTask();

    using stageMethod = void (CoatingTask::*)();
    static const std::array<stageMethod, 30> stages_;

public:
    CoatingTask(
        IConsumableTask<bool>& calibrationTask,
        IXAxisController& xAxisController,
        IYAxisController& yAxisController,
        IZAxisController& zAxisController,
        ISpindleController& spindleController,
        IHeaterController& heaterController
    );

    void start() override;
    void reset() override;
    void tick() override;
    [[nodiscard]] bool isFinished() const override;
    bool consumeResult() override;
};
}