#include "application/System/Tasks/Task/AxisTestTask/AxisTestResults.hpp"
#include "application/System/Tasks/Task/HeaterTestTask/HeaterTestResults.hpp"
#include "application/System/Tasks/Task/SpindleTestTask/SpindleTestResults.hpp"

#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

// TODO abstract it out and create a fake for Host
void Model::pollCoatingTask() {
    // if (targetBoard_.isCoatingTaskDone()) {
    //     const bool wasSuccessful =
    //         targetBoard_.consumeCoatingTaskResult();
    //     modelListener->handleCoatingTaskFinish(wasSuccessful);
    // }
}

void Model::pollCalibrationTask() {
    // if (targetBoard_.isCalibrationTaskDone()) {
    //     const bool wasSuccessful =
    //         targetBoard_.consumeCalibrationTaskResult();
    //     modelListener->handleCalibrationTaskFinish(wasSuccessful);
    // }
}

void Model::pollXAxisTestTask() {
    // if (targetBoard_.isXAxisTestTaskDone()) {
    //     const ATC::AxisTestResults results =
    //         targetBoard_.consumeXAxisTestTaskResult();
    //     modelListener->handleXAxisTestTaskFinish(results);
    // }
}

void Model::pollYAxisTestTask() {
    // if (targetBoard_.isYAxisTestTaskDone()) {
    //     const ATC::AxisTestResults results =
    //         targetBoard_.consumeYAxisTestTaskResult();
    //     modelListener->handleYAxisTestTaskFinish(results);
    // }
}

void Model::pollZAxisTestTask() {
    // if (targetBoard_.isZAxisTestTaskDone()) {
    //     const ATC::AxisTestResults results =
    //         targetBoard_.consumeZAxisTestTaskResult();
    //     modelListener->handleZAxisTestTaskFinish(results);
    // }
}

void Model::pollRotatorTestTask() {
    // if (targetBoard_.isRotatorTestTaskDone()) {
    //     const ATC::SpindleTestResults results =
    //         targetBoard_.consumeRotatorTestTaskResult();
    //     modelListener->handleRotatorTestTaskFinish(results);
    // }
}

void Model::pollHeaterTestTask() {
    // if (targetBoard_.isHeaterTestTaskDone()) {
    //     const ATC::HeaterTestResults results =
    //         targetBoard_.consumeHeaterTestTaskResult();
    //     modelListener->handleHeaterTestTaskFinish(results);
    // }
}

Model::Model() : modelListener(0) {}

void Model::tick() {
    pollCoatingTask();
    pollCalibrationTask();
    pollXAxisTestTask();
    pollYAxisTestTask();
    pollZAxisTestTask();
    pollRotatorTestTask();
    pollHeaterTestTask();
}

ATC::SystemApi& Model::getSystemApi() {
    return systemApi_;
}
