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

    void startRotation();

    void moveXAxisToHeaterFrontPosition();
    void waitForXAxisAtHeaterFrontPosition();

    void startTimedRotationInHeaterFront();
    void waitForTimedRotationToFinish();

    void moveXAxisToStartPosition();
    void waitForXAxisAtStartPosition();

    void stopRotation();
    void finishTask();

    using stageMethod = void (CoatingTask::*)();
    static const std::array<stageMethod, 25> stages_;

public:
    CoatingTask(
        IConsumableTask<bool>& calibrationTask,
        IXAxisController& xAxisController,
        IYAxisController& yAxisController,
        IZAxisController& zAxisController,
        ISpindleController& spindleController,
        IHeaterController& heaterController
    );

    virtual void start() override;
    virtual void reset() override;
    virtual void tick() override;
    virtual bool isFinished() const override;
    virtual bool consumeResult() override;
};
}