#include "application/UartLogger/UartLogger.hpp"

#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

Model::Model() : modelListener(0) {}

void Model::tick() {}

void Model::cancelCurrentTask() {
    UartLogger::debugPrint("Model::%s not implemented", __func__);
    // TODO implement
}

void Model::startCoatingSequence() {
    UartLogger::debugPrint("Model::%s not implemented", __func__);
    // TODO implement
}

bool Model::isCoatingSequenceFinished() {
    UartLogger::debugPrint("Model::%s not implemented", __func__);
    // TODO implement
    return true;
}

void Model::calibrate() {
    UartLogger::debugPrint("Model::%s not implemented", __func__);
    // TODO implement
}

bool Model::isCalibrationFinished() {
    UartLogger::debugPrint("Model::%s not implemented", __func__);
    // TODO implement
    return true;
}

void Model::increaseXAxisStart() {
    UartLogger::debugPrint("Model::%s not implemented", __func__);
    // TODO implement
}

void Model::decreaseXAxisStart() {
    UartLogger::debugPrint("Model::%s not implemented", __func__);
    // TODO implement
}

void Model::saveXAxisStart() {
    UartLogger::debugPrint("Model::%s not implemented", __func__);
    // TODO implement
}

uint32_t Model::getXAxisStart() {
    UartLogger::debugPrint("Model::%s not implemented", __func__);
    // TODO implement
    return 0;
}

void Model::increaseXAxisEnd() {
    UartLogger::debugPrint("Model::%s not implemented", __func__);
    // TODO implement
}

void Model::decreaseXAxisEnd() {
    UartLogger::debugPrint("Model::%s not implemented", __func__);
    // TODO implement
}

void Model::saveXAxisEnd() {
    UartLogger::debugPrint("Model::%s not implemented", __func__);
    // TODO implement
}

uint32_t Model::getXAxisEnd() {
    UartLogger::debugPrint("Model::%s not implemented", __func__);
    // TODO implement
    return 1000;
}

void Model::increaseXAxisSpeed() {
    UartLogger::debugPrint("Model::%s not implemented", __func__);
    // TODO implement
}

void Model::decreaseXAxisSpeed() {
    UartLogger::debugPrint("Model::%s not implemented", __func__);
    // TODO implement
}

void Model::saveXAxisSpeed() {
    UartLogger::debugPrint("Model::%s not implemented", __func__);
    // TODO implement
}

uint32_t Model::getXAxisSpeed() {
    UartLogger::debugPrint("Model::%s not implemented", __func__);
    // TODO implement
    return 100;
}

void Model::increaseYAxisStart() {
    UartLogger::debugPrint("Model::%s not implemented", __func__);
    // TODO implement
}

void Model::decreaseYAxisStart() {
    UartLogger::debugPrint("Model::%s not implemented", __func__);
    // TODO implement
}

void Model::saveYAxisStart() {
    UartLogger::debugPrint("Model::%s not implemented", __func__);
    // TODO implement
}

uint32_t Model::getYAxisStart() {
    UartLogger::debugPrint("Model::%s not implemented", __func__);
    // TODO implement
    return 0;
}

void Model::increaseYAxisEnd() {
    UartLogger::debugPrint("Model::%s not implemented", __func__);
    // TODO implement
}

void Model::decreaseYAxisEnd() {
    UartLogger::debugPrint("Model::%s not implemented", __func__);
    // TODO implement
}

void Model::saveYAxisEnd() {
    UartLogger::debugPrint("Model::%s not implemented", __func__);
    // TODO implement
}

uint32_t Model::getYAxisEnd() {
    UartLogger::debugPrint("Model::%s not implemented", __func__);
    // TODO implement
    return 1000;
}

void Model::increaseYAxisSpeed() {
    UartLogger::debugPrint("Model::%s not implemented", __func__);
    // TODO implement
}

void Model::decreaseYAxisSpeed() {
    UartLogger::debugPrint("Model::%s not implemented", __func__);
    // TODO implement
}

void Model::saveYAxisSpeed() {
    UartLogger::debugPrint("Model::%s not implemented", __func__);
    // TODO implement
}

uint32_t Model::getYAxisSpeed() {
    UartLogger::debugPrint("Model::%s not implemented", __func__);
    // TODO implement
    return 100;
}

void Model::increaseZAxisStart() {
    UartLogger::debugPrint("Model::%s not implemented", __func__);
    // TODO implement
}

void Model::decreaseZAxisStart() {
    UartLogger::debugPrint("Model::%s not implemented", __func__);
    // TODO implement
}

void Model::saveZAxisStart() {
    UartLogger::debugPrint("Model::%s not implemented", __func__);
    // TODO implement
}

uint32_t Model::getZAxisStart() {
    UartLogger::debugPrint("Model::%s not implemented", __func__);
    // TODO implement
    return 0;
}

void Model::increaseZAxisEnd() {
    UartLogger::debugPrint("Model::%s not implemented", __func__);
    // TODO implement
}

void Model::decreaseZAxisEnd() {
    UartLogger::debugPrint("Model::%s not implemented", __func__);
    // TODO implement
}

void Model::saveZAxisEnd() {
    UartLogger::debugPrint("Model::%s not implemented", __func__);
    // TODO implement
}

uint32_t Model::getZAxisEnd() {
    UartLogger::debugPrint("Model::%s not implemented", __func__);
    // TODO implement
    return 1000;
}

void Model::increaseZAxisSpeed() {
    UartLogger::debugPrint("Model::%s not implemented", __func__);
    // TODO implement
}

void Model::decreaseZAxisSpeed() {
    UartLogger::debugPrint("Model::%s not implemented", __func__);
    // TODO implement
}

void Model::saveZAxisSpeed() {
    UartLogger::debugPrint("Model::%s not implemented", __func__);
    // TODO implement
}

uint32_t Model::getZAxisSpeed() {
    UartLogger::debugPrint("Model::%s not implemented", __func__);
    // TODO implement
    return 100;
}

void Model::increaseRotationSpeed() {
    UartLogger::debugPrint("Model::%s not implemented", __func__);
    // TODO implement
}

void Model::decreaseRotationSpeed() {
    UartLogger::debugPrint("Model::%s not implemented", __func__);
    // TODO implement
}

void Model::saveRotationSpeed() {
    UartLogger::debugPrint("Model::%s not implemented", __func__);
    // TODO implement
}

uint32_t Model::getRotationSpeed() {
    UartLogger::debugPrint("Model::%s not implemented", __func__);
    // TODO implement
    return 100;
}

void Model::setClockwiseRotation() {
    UartLogger::debugPrint("Model::%s not implemented", __func__);
    // TODO implement
}

void Model::setCounterClockwiseRotation() {
    UartLogger::debugPrint("Model::%s not implemented", __func__);
    // TODO implement
}

void Model::saveRotationDirection() {
    UartLogger::debugPrint("Model::%s not implemented", __func__);
    // TODO implement
}

bool Model::isRotationClockwise() {
    UartLogger::debugPrint("Model::%s not implemented", __func__);
    // TODO implement
    return true;
}

void Model::testXAxis() {
    UartLogger::debugPrint("Model::%s not implemented", __func__);
    // TODO implement
}

void Model::testYAxis() {
    UartLogger::debugPrint("Model::%s not implemented", __func__);
    // TODO implement
}

void Model::testZAxis() {
    UartLogger::debugPrint("Model::%s not implemented", __func__);
    // TODO implement
}

void Model::testHeater() {
    UartLogger::debugPrint("Model::%s not implemented", __func__);
    // TODO implement
}