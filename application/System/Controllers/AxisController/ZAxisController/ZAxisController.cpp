#include "ZAxisController.hpp"

#include "application/System/Controllers/AxisMotionController/IAxisMotionController.hpp"

namespace ATC {
ZAxisController::ZAxisController(
    ILoggerSink& loggerSink,
    IAxisMotionController& axisMotionController
) :
    loggerSink_(loggerSink),
    axisMotionController_(axisMotionController) {}

void ZAxisController::init(const AxisPersistentConfig& config) {
    startPosition_ = config.startPosition;
    endPosition_ = config.endPosition;
}

void ZAxisController::tick() {}

bool ZAxisController::wasFaultReported() const {
    return axisMotionController_.wasFaultDetected();
}

void ZAxisController::moveToPosition(uint32_t position) {
    axisMotionController_.moveTo(position);
}

uint32_t ZAxisController::getCurrentPosition() const {
    return axisMotionController_.getCurrentPosition();
}

void ZAxisController::moveToMinLimitPosition() {
    axisMotionController_.moveToMinLimitSwitch();
}

bool ZAxisController::isAtMinLimitPosition() const {
    return axisMotionController_.isAtMinLimit();
}

void ZAxisController::moveToMaxLimitPosition() {
    axisMotionController_.moveToMaxLimitSwitch();
}

bool ZAxisController::isAtMaxLimitPosition() const {
    return axisMotionController_.isAtMaxLimit();
}

void ZAxisController::moveToHomePosition() {
    axisMotionController_.homeAxis();
}

bool ZAxisController::isAtHomePosition() const {
    return axisMotionController_.isAtMaxLimit();
}

void ZAxisController::moveToStartPosition() {
    axisMotionController_.moveTo(startPosition_);
}

bool ZAxisController::isAtStartPosition() const {
    return axisMotionController_.isAtPosition(startPosition_);
}

void ZAxisController::moveToEndPosition() {
    axisMotionController_.moveTo(endPosition_);
}

bool ZAxisController::isAtEndPosition() const {
    return axisMotionController_.isAtPosition(endPosition_);
}

void ZAxisController::setStartPosition(uint32_t value) {
    startPosition_ = value;
}

uint32_t ZAxisController::getStartPosition() const {
    return startPosition_;
}

void ZAxisController::setEndPosition(uint32_t value) {
    endPosition_ = value;
}

uint32_t ZAxisController::getEndPosition() const {
    return endPosition_;
}

void ZAxisController::setSpeedInMillimetersPerSecond(uint16_t value) {
    axisMotionController_.setMillimetersPerSecond(value);
}

uint16_t ZAxisController::getSpeedInMillimetersPerSecond() const {
    return axisMotionController_.getMillimetersPerSecond();
}

void ZAxisController::cancelMovement() {
    axisMotionController_.cancelMovement();
}
}