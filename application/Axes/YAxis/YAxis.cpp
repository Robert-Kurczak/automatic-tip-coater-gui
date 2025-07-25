#include "YAxis.hpp"
#include "application/UartLogger/UartLogger.hpp"

namespace ATC {
void YAxis::init() {}

void YAxis::tick() {}

void YAxis::startTestTask(YAxisTestTaskCallback callback) {
    UartLogger::debugPrint("YAxis::%s not implemented", __func__);
    // TODO implement

    YAxisTestResults results {
        .startLimitSwitchSuccess = false,
        .endLimitSwitchSuccess = false,
        .motorDriverSuccess = false
    };

    callback(results);
}

void YAxis::increaseStartPosition() {
    UartLogger::debugPrint("YAxis::%s not implemented", __func__);
    // TODO implement
}

void YAxis::decreaseStartPosition() {
    UartLogger::debugPrint("YAxis::%s not implemented", __func__);
    // TODO implement
}

void YAxis::saveStartPosition() {
    UartLogger::debugPrint("YAxis::%s not implemented", __func__);
    // TODO implement
}

uint32_t YAxis::getStartPosition() {
    UartLogger::debugPrint("YAxis::%s not implemented", __func__);
    // TODO implement
    return 0;
}

void YAxis::increaseEndPosition() {
    UartLogger::debugPrint("YAxis::%s not implemented", __func__);
    // TODO implement
}

void YAxis::decreaseEndPosition() {
    UartLogger::debugPrint("YAxis::%s not implemented", __func__);
    // TODO implement
}

void YAxis::saveEndPosition() {
    UartLogger::debugPrint("YAxis::%s not implemented", __func__);
    // TODO implement
}

uint32_t YAxis::getEndPosition() {
    UartLogger::debugPrint("YAxis::%s not implemented", __func__);
    // TODO implement
    return 1000;
}

void YAxis::increaseSpeed() {
    UartLogger::debugPrint("YAxis::%s not implemented", __func__);
    // TODO implement
}

void YAxis::decreaseSpeed() {
    UartLogger::debugPrint("YAxis::%s not implemented", __func__);
    // TODO implement
}

void YAxis::saveSpeed() {
    UartLogger::debugPrint("YAxis::%s not implemented", __func__);
    // TODO implement
}

uint32_t YAxis::getSpeed() {
    UartLogger::debugPrint("YAxis::%s not implemented", __func__);
    // TODO implement
    return 100;
}

}