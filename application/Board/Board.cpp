#include "Board.hpp"
#include "application/UartLogger/UartLogger.hpp"

namespace ATC {
Board::Board(XAxis& xAxis, YAxis& yAxis, ZAxis& zAxis) :
    xAxis_(xAxis),
    yAxis_(yAxis),
    zAxis_(zAxis) {}

void Board::cancelCurrentTask() {
    UartLogger::debugPrint("Board::%s not implemented", __func__);
    // TODO implement
}

void Board::startCoatingSequence() {
    UartLogger::debugPrint("Board::%s not implemented", __func__);
    // TODO implement
}

bool Board::isCoatingSequenceFinished() {
    UartLogger::debugPrint("Board::%s not implemented", __func__);
    // TODO implement
    return true;
}

void Board::calibrate() {
    UartLogger::debugPrint("Board::%s not implemented", __func__);
    // TODO implement
}

bool Board::isCalibrationFinished() {
    UartLogger::debugPrint("Board::%s not implemented", __func__);
    // TODO implement
    return true;
}

void Board::increaseXAxisStart() {
    xAxis_.increaseStartPosition();
}

void Board::decreaseXAxisStart() {
    xAxis_.decreaseStartPosition();
}

void Board::saveXAxisStart() {
    xAxis_.saveStartPosition();
}

uint32_t Board::getXAxisStart() {
    return xAxis_.getStartPosition();
}

void Board::increaseXAxisEnd() {
    xAxis_.increaseEndPosition();
}

void Board::decreaseXAxisEnd() {
    xAxis_.decreaseEndPosition();
}

void Board::saveXAxisEnd() {
    xAxis_.saveEndPosition();
}

uint32_t Board::getXAxisEnd() {
    return xAxis_.getEndPosition();
}

void Board::increaseXAxisSpeed() {
    xAxis_.increaseSpeed();
}

void Board::decreaseXAxisSpeed() {
    xAxis_.decreaseSpeed();
}

void Board::saveXAxisSpeed() {
    xAxis_.saveSpeed();
}

uint32_t Board::getXAxisSpeed() {
    return xAxis_.getSpeed();
}

void Board::increaseYAxisStart() {
    yAxis_.increaseStartPosition();
}

void Board::decreaseYAxisStart() {
    yAxis_.decreaseStartPosition();
}

void Board::saveYAxisStart() {
    yAxis_.saveStartPosition();
}

uint32_t Board::getYAxisStart() {
    return yAxis_.getStartPosition();
}

void Board::increaseYAxisEnd() {
    yAxis_.increaseEndPosition();
}

void Board::decreaseYAxisEnd() {
    yAxis_.decreaseEndPosition();
}

void Board::saveYAxisEnd() {
    yAxis_.saveEndPosition();
}

uint32_t Board::getYAxisEnd() {
    return yAxis_.getEndPosition();
}

void Board::increaseYAxisSpeed() {
    yAxis_.increaseSpeed();
}

void Board::decreaseYAxisSpeed() {
    yAxis_.decreaseSpeed();
}

void Board::saveYAxisSpeed() {
    yAxis_.saveSpeed();
}

uint32_t Board::getYAxisSpeed() {
    return yAxis_.getSpeed();
}

void Board::increaseZAxisStart() {
    zAxis_.increaseStartPosition();
}

void Board::decreaseZAxisStart() {
    zAxis_.decreaseStartPosition();
}

void Board::saveZAxisStart() {
    zAxis_.saveStartPosition();
}

uint32_t Board::getZAxisStart() {
    return zAxis_.getStartPosition();
}

void Board::increaseZAxisEnd() {
    zAxis_.increaseEndPosition();
}

void Board::decreaseZAxisEnd() {
    zAxis_.decreaseEndPosition();
}

void Board::saveZAxisEnd() {
    zAxis_.saveEndPosition();
}

uint32_t Board::getZAxisEnd() {
    return zAxis_.getEndPosition();
}

void Board::increaseZAxisSpeed() {
    zAxis_.increaseSpeed();
}

void Board::decreaseZAxisSpeed() {
    zAxis_.decreaseSpeed();
}

void Board::saveZAxisSpeed() {
    zAxis_.saveSpeed();
}

uint32_t Board::getZAxisSpeed() {
    return zAxis_.getSpeed();
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

void Board::testXAxis() {
    UartLogger::debugPrint("Board::%s not implemented", __func__);
    // TODO implement
}

void Board::testYAxis() {
    UartLogger::debugPrint("Board::%s not implemented", __func__);
    // TODO implement
}

void Board::testZAxis() {
    UartLogger::debugPrint("Board::%s not implemented", __func__);
    // TODO implement
}

void Board::testHeater() {
    UartLogger::debugPrint("Board::%s not implemented", __func__);
    // TODO implement
}
}