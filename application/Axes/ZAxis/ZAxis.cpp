#include "ZAxis.hpp"
#include "application/UartLogger/UartLogger.hpp"


namespace ATC {
void ZAxis::init() {}

void ZAxis::increaseStartPosition() {
    UartLogger::debugPrint("ZAxis::%s not implemented", __func__);
    // TODO implement
}

void ZAxis::decreaseStartPosition() {
    UartLogger::debugPrint("ZAxis::%s not implemented", __func__);
    // TODO implement
}

void ZAxis::saveStartPosition() {
    UartLogger::debugPrint("ZAxis::%s not implemented", __func__);
    // TODO implement
}

uint32_t ZAxis::getStartPosition() {
    UartLogger::debugPrint("ZAxis::%s not implemented", __func__);
    // TODO implement
    return 0;
}

void ZAxis::increaseEndPosition() {
    UartLogger::debugPrint("ZAxis::%s not implemented", __func__);
    // TODO implement
}

void ZAxis::decreaseEndPosition() {
    UartLogger::debugPrint("ZAxis::%s not implemented", __func__);
    // TODO implement
}

void ZAxis::saveEndPosition() {
    UartLogger::debugPrint("ZAxis::%s not implemented", __func__);
    // TODO implement
}

uint32_t ZAxis::getEndPosition() {
    UartLogger::debugPrint("ZAxis::%s not implemented", __func__);
    // TODO implement
    return 1000;
}

void ZAxis::increaseSpeed() {
    UartLogger::debugPrint("ZAxis::%s not implemented", __func__);
    // TODO implement
}

void ZAxis::decreaseSpeed() {
    UartLogger::debugPrint("ZAxis::%s not implemented", __func__);
    // TODO implement
}

void ZAxis::saveSpeed() {
    UartLogger::debugPrint("ZAxis::%s not implemented", __func__);
    // TODO implement
}

uint32_t ZAxis::getSpeed() {
    UartLogger::debugPrint("ZAxis::%s not implemented", __func__);
    // TODO implement
    return 100;
}

}