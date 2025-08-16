#include "CommonAxisController.hpp"

namespace ATC {
void CommonAxisController::setStartPosition(uint32_t value) {
    startPosition_ = value;
}

uint32_t CommonAxisController::getStartPosition() const {
    return startPosition_;
}

void CommonAxisController::setEndPosition(uint32_t value) {
    endPosition_ = value;
}

uint32_t CommonAxisController::getEndPosition() const {
    return endPosition_;
}

void CommonAxisController::setSpeed(uint32_t value) {
    speed_ = value;
}

uint32_t CommonAxisController::getSpeed() const {
    return speed_;
}
}