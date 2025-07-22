#include "Board.hpp"
#include "application/UartLogger/UartLogger.hpp"

namespace ATC {
Board::Board(BoardDevices& devices) : devices_(devices) {}

void Board::init() {
    devices_.display.init();
    devices_.touchController.init();
}

void Board::tick() {}

void Board::startCoatingTask(TaskCallback callback) {
    UartLogger::debugPrint("Board::%s not implemented", __func__);
    // TODO implement
    callback(false);
}

void Board::startCalibrationTask(TaskCallback callback) {
    UartLogger::debugPrint("Board::%s not implemented", __func__);
    // TODO implement
    callback(false);
}

void Board::startXAxisTestTask(TaskCallback callback) {
    UartLogger::debugPrint("Board::%s not implemented", __func__);
    // TODO implement
    callback(false);
}

void Board::startYAxisTestTask(TaskCallback callback) {
    UartLogger::debugPrint("Board::%s not implemented", __func__);
    // TODO implement
    callback(false);
}

void Board::startZAxisTestTask(TaskCallback callback) {
    UartLogger::debugPrint("Board::%s not implemented", __func__);
    // TODO implement
    callback(false);
}

void Board::startHeaterTestTask(TaskCallback callback) {
    UartLogger::debugPrint("Board::%s not implemented", __func__);
    // TODO implement
    callback(false);
}

void Board::startRotationTestTask(TaskCallback callback) {
    UartLogger::debugPrint("Board::%s not implemented", __func__);
    // TODO implement
    callback(false);
}

void Board::cancelCurrentTask() {
    UartLogger::debugPrint("Board::%s not implemented", __func__);
    // TODO implement
}

void Board::increaseXAxisStart() {
    devices_.xAxis.increaseStartPosition();
}

void Board::decreaseXAxisStart() {
    devices_.xAxis.decreaseStartPosition();
}

void Board::saveXAxisStart() {
    devices_.xAxis.saveStartPosition();
}

uint32_t Board::getXAxisStart() {
    return devices_.xAxis.getStartPosition();
}

void Board::increaseXAxisEnd() {
    devices_.xAxis.increaseEndPosition();
}

void Board::decreaseXAxisEnd() {
    devices_.xAxis.decreaseEndPosition();
}

void Board::saveXAxisEnd() {
    devices_.xAxis.saveEndPosition();
}

uint32_t Board::getXAxisEnd() {
    return devices_.xAxis.getEndPosition();
}

void Board::increaseXAxisSpeed() {
    devices_.xAxis.increaseSpeed();
}

void Board::decreaseXAxisSpeed() {
    devices_.xAxis.decreaseSpeed();
}

void Board::saveXAxisSpeed() {
    devices_.xAxis.saveSpeed();
}

uint32_t Board::getXAxisSpeed() {
    return devices_.xAxis.getSpeed();
}

void Board::increaseYAxisStart() {
    devices_.yAxis.increaseStartPosition();
}

void Board::decreaseYAxisStart() {
    devices_.yAxis.decreaseStartPosition();
}

void Board::saveYAxisStart() {
    devices_.yAxis.saveStartPosition();
}

uint32_t Board::getYAxisStart() {
    return devices_.yAxis.getStartPosition();
}

void Board::increaseYAxisEnd() {
    devices_.yAxis.increaseEndPosition();
}

void Board::decreaseYAxisEnd() {
    devices_.yAxis.decreaseEndPosition();
}

void Board::saveYAxisEnd() {
    devices_.yAxis.saveEndPosition();
}

uint32_t Board::getYAxisEnd() {
    return devices_.yAxis.getEndPosition();
}

void Board::increaseYAxisSpeed() {
    devices_.yAxis.increaseSpeed();
}

void Board::decreaseYAxisSpeed() {
    devices_.yAxis.decreaseSpeed();
}

void Board::saveYAxisSpeed() {
    devices_.yAxis.saveSpeed();
}

uint32_t Board::getYAxisSpeed() {
    return devices_.yAxis.getSpeed();
}

void Board::increaseZAxisStart() {
    devices_.zAxis.increaseStartPosition();
}

void Board::decreaseZAxisStart() {
    devices_.zAxis.decreaseStartPosition();
}

void Board::saveZAxisStart() {
    devices_.zAxis.saveStartPosition();
}

uint32_t Board::getZAxisStart() {
    return devices_.zAxis.getStartPosition();
}

void Board::increaseZAxisEnd() {
    devices_.zAxis.increaseEndPosition();
}

void Board::decreaseZAxisEnd() {
    devices_.zAxis.decreaseEndPosition();
}

void Board::saveZAxisEnd() {
    devices_.zAxis.saveEndPosition();
}

uint32_t Board::getZAxisEnd() {
    return devices_.zAxis.getEndPosition();
}

void Board::increaseZAxisSpeed() {
    devices_.zAxis.increaseSpeed();
}

void Board::decreaseZAxisSpeed() {
    devices_.zAxis.decreaseSpeed();
}

void Board::saveZAxisSpeed() {
    devices_.zAxis.saveSpeed();
}

uint32_t Board::getZAxisSpeed() {
    return devices_.zAxis.getSpeed();
}

void Board::increaseRotationSpeed() {
    UartLogger::debugPrint("Board::%s not implemented", __func__);
    // TODO implement
}

void Board::decreaseRotationSpeed() {
    UartLogger::debugPrint("Board::%s not implemented", __func__);
    // TODO implement
}

void Board::saveRotationSpeed() {
    UartLogger::debugPrint("Board::%s not implemented", __func__);
    // TODO implement
}

uint32_t Board::getRotationSpeed() {
    UartLogger::debugPrint("Board::%s not implemented", __func__);
    // TODO implement
    return 100;
}

void Board::setClockwiseRotation() {
    UartLogger::debugPrint("Board::%s not implemented", __func__);
    // TODO implement
}

void Board::setCounterClockwiseRotation() {
    UartLogger::debugPrint("Board::%s not implemented", __func__);
    // TODO implement
}

void Board::saveRotationDirection() {
    UartLogger::debugPrint("Board::%s not implemented", __func__);
    // TODO implement
}

bool Board::isRotationClockwise() {
    UartLogger::debugPrint("Board::%s not implemented", __func__);
    // TODO implement
    return true;
}

void Board::increaseRotationTime() {
    UartLogger::debugPrint("Board::%s not implemented", __func__);
    // TODO implement
}

void Board::decreaseRotationTime() {
    UartLogger::debugPrint("Board::%s not implemented", __func__);
    // TODO implement
}

void Board::saveRotationTime() {
    UartLogger::debugPrint("Board::%s not implemented", __func__);
    // TODO implement
}

uint32_t Board::getRotationTime() {
    UartLogger::debugPrint("Board::%s not implemented", __func__);
    // TODO implement
    return 3;
}

void Board::setHeaterOn() {
    UartLogger::debugPrint("Board::%s not implemented", __func__);
    // TODO implement
}

void Board::setHeaterOff() {
    UartLogger::debugPrint("Board::%s not implemented", __func__);
    // TODO implement
}

void Board::saveHeaterState() {
    UartLogger::debugPrint("Board::%s not implemented", __func__);
    // TODO implement
}

bool Board::isHeaterOn() {
    UartLogger::debugPrint("Board::%s not implemented", __func__);
    // TODO implement
    return false;
}

void Board::increaseHeaterTemperature() {
    UartLogger::debugPrint("Board::%s not implemented", __func__);
    // TODO implement
}

void Board::decreaseHeaterTemperature() {
    UartLogger::debugPrint("Board::%s not implemented", __func__);
    // TODO implement
}

void Board::saveHeaterTemperature() {
    UartLogger::debugPrint("Board::%s not implemented", __func__);
    // TODO implement
}

uint32_t Board::getHeaterTemperature() {
    UartLogger::debugPrint("Board::%s not implemented", __func__);
    // TODO implement
    return 100;
}

void Board::drawOnDisplay(
    const std::span<const uint16_t>& frameBuffer,
    const Rectangle& window
) {
    devices_.display.draw(frameBuffer, window);
}

Vector2 Board::readTouchScreenPosition() {
    return devices_.touchController.readPosition();
}
}