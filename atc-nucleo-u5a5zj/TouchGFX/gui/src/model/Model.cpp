#include "TargetBoard.hpp"
#include "application/Axes/XAxis/XAxisTestResults.hpp"

#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

// TODO abstract it out and create a fake for Host
static ATC::TargetBoard targetBoard_ = ATC::TargetBoard::getBoard();

Model::Model() : modelListener(0) {}

void Model::tick() {}

void Model::startCoatingTask() {
    auto callback = [this](bool wasSuccessful) {
        modelListener->handleCoatingTaskFinish(wasSuccessful);
    };

    targetBoard_.startCoatingTask(callback);
}

void Model::startCalibrationTask() {
    auto callback = [this](bool wasSuccessful) {
        modelListener->handleCalibrationTaskFinish(wasSuccessful);
    };

    targetBoard_.startCalibrationTask(callback);
}

void Model::startXAxisTestTask() {
    auto callback = [this](ATC::XAxisTestResults results) {
        modelListener->handleXAxisTestTaskFinish(results);
    };

    targetBoard_.startXAxisTestTask(callback);
}

void Model::startYAxisTestTask() {
    auto callback = [this](ATC::YAxisTestResults results) {
        modelListener->handleYAxisTestTaskFinish(results);
    };

    targetBoard_.startYAxisTestTask(callback);
}

void Model::startZAxisTestTask() {
    auto callback = [this](ATC::ZAxisTestResults results) {
        modelListener->handleZAxisTestTaskFinish(results);
    };

    targetBoard_.startZAxisTestTask(callback);
}

void Model::startRotationTestTask() {
    auto callback = [this](ATC::RotatorTestResults results) {
        modelListener->handleRotatorTestTaskFinish(results);
    };

    targetBoard_.startRotationTestTask(callback);
}

void Model::startHeaterTestTask() {
    auto callback = [this](ATC::HeaterTestResults results) {
        modelListener->handleHeaterTestTaskFinish(results);
    };

    targetBoard_.startHeaterTestTask(callback);
}

void Model::cancelCurrentTask() {
    targetBoard_.cancelCurrentTask();
}

void Model::increaseXAxisStart() {
    targetBoard_.increaseXAxisStart();
}

void Model::decreaseXAxisStart() {
    targetBoard_.decreaseXAxisStart();
}

void Model::saveXAxisStart() {
    targetBoard_.saveXAxisStart();
}

uint32_t Model::getXAxisStart() {
    return targetBoard_.getXAxisStart();
}

void Model::increaseXAxisEnd() {
    targetBoard_.increaseXAxisEnd();
}

void Model::decreaseXAxisEnd() {
    targetBoard_.decreaseXAxisEnd();
}

void Model::saveXAxisEnd() {
    targetBoard_.saveXAxisEnd();
}

uint32_t Model::getXAxisEnd() {
    return targetBoard_.getXAxisEnd();
}

void Model::increaseXAxisSpeed() {
    targetBoard_.increaseXAxisSpeed();
}

void Model::decreaseXAxisSpeed() {
    targetBoard_.decreaseXAxisSpeed();
}

void Model::saveXAxisSpeed() {
    targetBoard_.saveXAxisSpeed();
}

uint32_t Model::getXAxisSpeed() {
    return targetBoard_.getXAxisSpeed();
}

void Model::increaseYAxisStart() {
    targetBoard_.increaseYAxisStart();
}

void Model::decreaseYAxisStart() {
    targetBoard_.decreaseYAxisStart();
}

void Model::saveYAxisStart() {
    targetBoard_.saveYAxisStart();
}

uint32_t Model::getYAxisStart() {
    return targetBoard_.getYAxisStart();
}

void Model::increaseYAxisEnd() {
    targetBoard_.increaseYAxisEnd();
}

void Model::decreaseYAxisEnd() {
    targetBoard_.decreaseYAxisEnd();
}

void Model::saveYAxisEnd() {
    targetBoard_.saveYAxisEnd();
}

uint32_t Model::getYAxisEnd() {
    return targetBoard_.getYAxisEnd();
}

void Model::increaseYAxisSpeed() {
    targetBoard_.increaseYAxisSpeed();
}

void Model::decreaseYAxisSpeed() {
    targetBoard_.decreaseYAxisSpeed();
}

void Model::saveYAxisSpeed() {
    targetBoard_.saveYAxisSpeed();
}

uint32_t Model::getYAxisSpeed() {
    return targetBoard_.getYAxisSpeed();
}

void Model::increaseZAxisStart() {
    targetBoard_.increaseZAxisStart();
}

void Model::decreaseZAxisStart() {
    targetBoard_.decreaseZAxisStart();
}

void Model::saveZAxisStart() {
    targetBoard_.saveZAxisStart();
}

uint32_t Model::getZAxisStart() {
    return targetBoard_.getZAxisStart();
}

void Model::increaseZAxisEnd() {
    targetBoard_.increaseZAxisEnd();
}

void Model::decreaseZAxisEnd() {
    targetBoard_.decreaseZAxisEnd();
}

void Model::saveZAxisEnd() {
    targetBoard_.saveZAxisEnd();
}

uint32_t Model::getZAxisEnd() {
    return targetBoard_.getZAxisEnd();
}

void Model::increaseZAxisSpeed() {
    targetBoard_.increaseZAxisSpeed();
}

void Model::decreaseZAxisSpeed() {
    targetBoard_.decreaseZAxisSpeed();
}

void Model::saveZAxisSpeed() {
    targetBoard_.saveZAxisSpeed();
}

uint32_t Model::getZAxisSpeed() {
    return targetBoard_.getZAxisSpeed();
}

void Model::increaseRotationSpeed() {
    targetBoard_.increaseRotationSpeed();
}

void Model::decreaseRotationSpeed() {
    targetBoard_.decreaseRotationSpeed();
}

void Model::saveRotationSpeed() {
    targetBoard_.saveRotationSpeed();
}

uint32_t Model::getRotationSpeed() {
    return targetBoard_.getRotationSpeed();
}

void Model::setClockwiseRotation() {
    targetBoard_.setClockwiseRotation();
}

void Model::setCounterClockwiseRotation() {
    targetBoard_.setCounterClockwiseRotation();
}

void Model::saveRotationDirection() {
    targetBoard_.saveRotationDirection();
}

bool Model::isRotationClockwise() {
    return targetBoard_.isRotationClockwise();
}

void Model::increaseRotationTime() {
    targetBoard_.increaseRotationTime();
}

void Model::decreaseRotationTime() {
    targetBoard_.decreaseRotationTime();
}

void Model::saveRotationTime() {
    targetBoard_.saveRotationTime();
}

uint32_t Model::getRotationTime() {
    return targetBoard_.getRotationTime();
}

void Model::setHeaterOn() {
    targetBoard_.setHeaterOn();
}

void Model::setHeaterOff() {
    targetBoard_.setHeaterOff();
}

void Model::saveHeaterState() {
    targetBoard_.saveHeaterState();
}

bool Model::isHeaterOn() {
    return targetBoard_.isHeaterOn();
}

void Model::increaseHeaterTemperature() {
    targetBoard_.increaseHeaterTemperature();
}

void Model::decreaseHeaterTemperature() {
    targetBoard_.decreaseHeaterTemperature();
}

void Model::saveHeaterTemperature() {
    targetBoard_.saveHeaterTemperature();
}

uint32_t Model::getHeaterTemperature() {
    return targetBoard_.getHeaterTemperature();
}