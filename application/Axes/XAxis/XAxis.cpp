#include "XAxis.hpp"
#include "application/UartLogger/UartLogger.hpp"


namespace ATC {
void XAxis::init() {}

void XAxis::tick() {}

void XAxis::startTestTask(XAxisTestTaskCallback callback) {
    UartLogger::debugPrint("XAxis::%s not implemented", __func__);
    // TODO implement

    XAxisTestResults results {
        .startLimitSwitchSuccess = false,
        .endLimitSwitchSuccess = false,
        .motorDriverSuccess = false
    };

    callback(results);
}

void XAxis::increaseStartPosition() {
    UartLogger::debugPrint("XAxis::%s not implemented", __func__);
    // TODO implement
}

void XAxis::decreaseStartPosition() {
    UartLogger::debugPrint("XAxis::%s not implemented", __func__);
    // TODO implement
}

void XAxis::saveStartPosition() {
    UartLogger::debugPrint("XAxis::%s not implemented", __func__);
    // TODO implement
}

uint32_t XAxis::getStartPosition() {
    UartLogger::debugPrint("XAxis::%s not implemented", __func__);
    // TODO implement
    return 0;
}

void XAxis::increaseEndPosition() {
    UartLogger::debugPrint("XAxis::%s not implemented", __func__);
    // TODO implement
}

void XAxis::decreaseEndPosition() {
    UartLogger::debugPrint("XAxis::%s not implemented", __func__);
    // TODO implement
}

void XAxis::saveEndPosition() {
    UartLogger::debugPrint("XAxis::%s not implemented", __func__);
    // TODO implement
}

uint32_t XAxis::getEndPosition() {
    UartLogger::debugPrint("XAxis::%s not implemented", __func__);
    // TODO implement
    return 1000;
}

void XAxis::increaseSpeed() {
    UartLogger::debugPrint("XAxis::%s not implemented", __func__);
    // TODO implement
}

void XAxis::decreaseSpeed() {
    UartLogger::debugPrint("XAxis::%s not implemented", __func__);
    // TODO implement
}

void XAxis::saveSpeed() {
    UartLogger::debugPrint("XAxis::%s not implemented", __func__);
    // TODO implement
}

uint32_t XAxis::getSpeed() {
    UartLogger::debugPrint("XAxis::%s not implemented", __func__);
    // TODO implement
    return 100;
}

}