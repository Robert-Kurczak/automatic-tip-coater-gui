#include "Heater.hpp"
#include "application/UartLogger/UartLogger.hpp"

namespace ATC {
void Heater::init() {}

void Heater::setOn() {
    UartLogger::debugPrint("Heater::%s not implemented", __func__);
    // TODO implement
}

void Heater::setOff() {
    UartLogger::debugPrint("Heater::%s not implemented", __func__);
    // TODO implement
}

void Heater::saveState() {
    UartLogger::debugPrint("Heater::%s not implemented", __func__);
    // TODO implement
}

bool Heater::isOn() {
    UartLogger::debugPrint("Heater::%s not implemented", __func__);
    // TODO implement
    return false;
}

void Heater::increaseTemperature() {
    UartLogger::debugPrint("Heater::%s not implemented", __func__);
    // TODO implement
}

void Heater::decreaseTemperature() {
    UartLogger::debugPrint("Heater::%s not implemented", __func__);
    // TODO implement
}

void Heater::saveTemperature() {
    UartLogger::debugPrint("Heater::%s not implemented", __func__);
    // TODO implement
}

uint32_t Heater::getTemperature() {
    UartLogger::debugPrint("Heater::%s not implemented", __func__);
    // TODO implement
    return 200;
}
}