#include "application/System/Tasks/Task/AxisTestTask/AxisTestResults.hpp"
#include "application/System/Tasks/Task/HeaterTestTask/HeaterTestResults.hpp"
#include "application/System/Tasks/Task/SpindleTestTask/SpindleTestResults.hpp"

#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

void Model::pollCoatingTask() {
    ATC::IConsumableTaskService<bool>& task =
        systemApi_.tasks.coatingTask;

    if (task.isFinished()) {
        const bool wasSuccessful = task.consumeResult();
        modelListener->handleCoatingTaskFinish(wasSuccessful);
    }
}

void Model::pollCalibrationTask() {
    ATC::IConsumableTaskService<bool>& task =
        systemApi_.tasks.calibrationTask;

    if (task.isFinished()) {
        const bool wasSuccessful = task.consumeResult();
        modelListener->handleCalibrationTaskFinish(wasSuccessful);
    }
}

void Model::pollXAxisTestTask() {
    ATC::IConsumableTaskService<ATC::AxisTestResults>& task =
        systemApi_.tasks.xAxisTestTask;

    if (task.isFinished()) {
        const ATC::AxisTestResults results = task.consumeResult();
        modelListener->handleXAxisTestTaskFinish(results);
    }
}

void Model::pollYAxisTestTask() {
    ATC::IConsumableTaskService<ATC::AxisTestResults>& task =
        systemApi_.tasks.yAxisTestTask;

    if (task.isFinished()) {
        const ATC::AxisTestResults results = task.consumeResult();
        modelListener->handleYAxisTestTaskFinish(results);
    }
}

void Model::pollZAxisTestTask() {
    ATC::IConsumableTaskService<ATC::AxisTestResults>& task =
        systemApi_.tasks.zAxisTestTask;

    if (task.isFinished()) {
        const ATC::AxisTestResults results = task.consumeResult();
        modelListener->handleZAxisTestTaskFinish(results);
    }
}

void Model::pollSpindleTestTask() {
    ATC::IConsumableTaskService<ATC::SpindleTestResults>& task =
        systemApi_.tasks.spindleTestTask;

    if (task.isFinished()) {
        const ATC::SpindleTestResults results = task.consumeResult();
        modelListener->handleRotatorTestTaskFinish(results);
    }
}

void Model::pollHeaterTestTask() {
    ATC::IConsumableTaskService<ATC::HeaterTestResults>& task =
        systemApi_.tasks.heaterTestTask;

    if (task.isFinished()) {
        const ATC::HeaterTestResults results = task.consumeResult();
        modelListener->handleHeaterTestTaskFinish(results);
    }
}

Model::Model() : modelListener(0) {}

void Model::tick() {
    pollCoatingTask();
    pollCalibrationTask();
    pollXAxisTestTask();
    pollYAxisTestTask();
    pollZAxisTestTask();
    pollSpindleTestTask();
    pollHeaterTestTask();
}

ATC::SystemApi& Model::getSystemApi() {
    return systemApi_;
}
