#include "Board.hpp"
#include "application/System/Logger/ILogger.hpp"
#include <source_location>

namespace ATC {
Board::Board(BoardDevices& devices, ILogger& logger) :
    devices_(devices),
    logger_(logger) {}

void Board::init() {
    devices_.xAxis.init();
    devices_.yAxis.init();
    devices_.zAxis.init();
    devices_.rotator.init();
    devices_.heater.init();
    devices_.display.init();
    devices_.touchController.init();
}

void Board::tick() {}

void Board::startCoatingTask(TaskCallback callback) {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
    callback(false);
}

void Board::startCalibrationTask(TaskCallback callback) {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
    callback(false);
}

void Board::startXAxisTestTask(AxisTestTaskCallback callback) {
    devices_.xAxis.startTestTask(callback);
}

void Board::startYAxisTestTask(AxisTestTaskCallback callback) {
    devices_.yAxis.startTestTask(callback);
}

void Board::startZAxisTestTask(AxisTestTaskCallback callback) {
    devices_.zAxis.startTestTask(callback);
}

void Board::startRotationTestTask(RotatorTestTaskCallback callback) {
    devices_.rotator.startTestTask(callback);
}

void Board::startHeaterTestTask(HeaterTestTaskCallback callback) {
    devices_.heater.startTestTask(callback);
}

void Board::cancelCurrentTask() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
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

// TODO change "Rotation" to "Rotator"
void Board::increaseRotationSpeed() {
    devices_.rotator.increaseSpeed();
}

void Board::decreaseRotationSpeed() {
    devices_.rotator.decreaseSpeed();
}

void Board::saveRotationSpeed() {
    devices_.rotator.saveSpeed();
}

uint32_t Board::getRotationSpeed() {
    return devices_.rotator.getSpeed();
}

void Board::setClockwiseRotation() {
    devices_.rotator.setDirectionClockwise();
}

void Board::setCounterClockwiseRotation() {
    devices_.rotator.setDirectionCounterClockwise();
}

void Board::saveRotationDirection() {
    devices_.rotator.setDirectionClockwise();
}

bool Board::isRotationClockwise() {
    return devices_.rotator.isDirectionClockwise();
}

void Board::increaseRotationTime() {
    return devices_.rotator.increaseRotationTime();
}

void Board::decreaseRotationTime() {
    return devices_.rotator.decreaseRotationTime();
}

void Board::saveRotationTime() {
    return devices_.rotator.saveRotationTime();
}

uint32_t Board::getRotationTime() {
    return devices_.rotator.getRotationTime();
}

void Board::setHeaterOn() {
    devices_.heater.setOn();
}

void Board::setHeaterOff() {
    devices_.heater.setOff();
}

void Board::saveHeaterState() {
    devices_.heater.saveState();
}

bool Board::isHeaterOn() {
    return devices_.heater.isOn();
}

void Board::increaseHeaterTemperature() {
    devices_.heater.increaseTemperature();
}

void Board::decreaseHeaterTemperature() {
    devices_.heater.decreaseTemperature();
}

void Board::saveHeaterTemperature() {
    devices_.heater.saveTemperature();
}

uint32_t Board::getHeaterTemperature() {
    return devices_.heater.getTemperature();
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