#pragma once

#include "../ITask.hpp"
#include "application/System/Board/BoardDevices.hpp"

#include <array>

namespace ATC {
class CoatingTask : public ITask<bool> {
private:
    BoardDevices& devices_;

    TaskState state_ = TaskState::IDLE;
    bool wasSuccessful_ = false;

    void resetStates();

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
    
    static constexpr std::array<stageMethod, 25> stages_ {
        &CoatingTask::moveAxesToInitialPosition,
        &CoatingTask::waitForAxesAtInitialPosition,

        &CoatingTask::moveZAxisToEndPosition,
        &CoatingTask::waitForZAxisAtEndPosition,

        &CoatingTask::detectTipWithYAxis,
        &CoatingTask::waitForTipDetection,

        &CoatingTask::moveYAxisToCoatingPosition,
        &CoatingTask::waitForYAxisAtCoatingPosition,

        &CoatingTask::moveZAxisToStartPosition,
        &CoatingTask::waitForZAxisAtStartPosition,

        &CoatingTask::moveXAxisToEndPosition,
        &CoatingTask::waitForXAxisAtEndPosition,

        &CoatingTask::moveZAxisToEndPosition,
        &CoatingTask::waitForZAxisAtEndPosition,

        &CoatingTask::startRotation,

        &CoatingTask::moveXAxisToHeaterFrontPosition,
        &CoatingTask::waitForXAxisAtHeaterFrontPosition,

        &CoatingTask::startTimedRotationInHeaterFront,
        &CoatingTask::waitForTimedRotationToFinish,

        &CoatingTask::moveXAxisToStartPosition,
        &CoatingTask::waitForXAxisAtStartPosition,

        &CoatingTask::stopRotation,

        &CoatingTask::moveZAxisToStartPosition,
        &CoatingTask::waitForZAxisAtEndPosition,

        &CoatingTask::finishTask
    };

    uint8_t currentStage_ = 0;

public:
    CoatingTask(BoardDevices& devices);

    virtual void start() override;
    virtual void tick() override;
    virtual bool isFinished() const override;
    virtual bool consumeResult() override;
};
}