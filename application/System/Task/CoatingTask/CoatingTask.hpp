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
    void moveZAxisToEndPosition();
    void detectTipWithYAxis();
    void moveYAxisToCoatingPosition();
    void moveZAxisToStartPosition();
    void moveXAxisToEndPosition();
    void startRotation();
    void moveXAxisToHeaterFront();
    void startTimedRotationInHeaterFront();
    void waitForTimedRotationToFinish();
    void moveXAxisToStartPosition();
    void stopRotation();
    void finishTask();

    using stageMethod = void (CoatingTask::*)();

    static constexpr std::array<stageMethod, 15> stages_ {
        &CoatingTask::moveAxesToInitialPosition,
        &CoatingTask::moveZAxisToEndPosition,
        &CoatingTask::detectTipWithYAxis,
        &CoatingTask::moveYAxisToCoatingPosition,
        &CoatingTask::moveZAxisToStartPosition,
        &CoatingTask::moveXAxisToEndPosition,
        &CoatingTask::moveZAxisToEndPosition,
        &CoatingTask::startRotation,
        &CoatingTask::moveXAxisToHeaterFront,
        &CoatingTask::startTimedRotationInHeaterFront,
        &CoatingTask::waitForTimedRotationToFinish,
        &CoatingTask::moveXAxisToStartPosition,
        &CoatingTask::stopRotation,
        &CoatingTask::moveZAxisToStartPosition,
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