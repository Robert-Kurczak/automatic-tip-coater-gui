#include "Rotator.hpp"
#include "application/UartLogger/UartLogger.hpp"

namespace ATC {
void Rotator::init() {}

void Rotator::tick() {}

void Rotator::startTestTask(RotatorTestTaskCallback callback) {
    UartLogger::debugPrint("Rotator::%s not implemented", __func__);
    // TODO implement

    RotatorTestResults results {.motorDriverSuccess = false};

    callback(results);
}

void Rotator::increaseSpeed() {
    UartLogger::debugPrint("Rotator::%s not implemented", __func__);
    // TODO implement
}

void Rotator::decreaseSpeed() {
    UartLogger::debugPrint("Rotator::%s not implemented", __func__);
    // TODO implement
}

void Rotator::saveSpeed() {
    UartLogger::debugPrint("Rotator::%s not implemented", __func__);
    // TODO implement
}

uint32_t Rotator::getSpeed() {
    UartLogger::debugPrint("Rotator::%s not implemented", __func__);
    // TODO implement
    return 10;
}

void Rotator::setDirectionClockwise() {
    UartLogger::debugPrint("Rotator::%s not implemented", __func__);
    // TODO implement
}

void Rotator::setDirectionCounterClockwise() {
    UartLogger::debugPrint("Rotator::%s not implemented", __func__);
    // TODO implement
}

void Rotator::saveDirection() {
    UartLogger::debugPrint("Rotator::%s not implemented", __func__);
    // TODO implement
}

bool Rotator::isDirectionClockwise() {
    UartLogger::debugPrint("Rotator::%s not implemented", __func__);
    // TODO implement
    return true;
}

void Rotator::increaseRotationTime() {
    UartLogger::debugPrint("Rotator::%s not implemented", __func__);
    // TODO implement
}

void Rotator::decreaseRotationTime() {
    UartLogger::debugPrint("Rotator::%s not implemented", __func__);
    // TODO implement
}

void Rotator::saveRotationTime() {
    UartLogger::debugPrint("Rotator::%s not implemented", __func__);
    // TODO implement
}

uint32_t Rotator::getRotationTime() {
    UartLogger::debugPrint("Rotator::%s not implemented", __func__);
    // TODO implement
    return 5;
}
}