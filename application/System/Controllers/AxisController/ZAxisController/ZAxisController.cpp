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
    startPositionInMicrometers_ = config.startPositionInMicrometers;
    endPositionInMicrometers_ = config.endPositionInMicrometers;

    axisMotionController_.init();
    axisMotionController_.setMillimetersPerSecond(
        config.speedInMillimetersPerSecond
    );
}

void ZAxisController::tick() {
    axisMotionController_.tick();
}

bool ZAxisController::wasFaultReported() const {
    return axisMotionController_.wasFaultDetected();
}

void ZAxisController::moveToPositionInMicrometers(uint32_t value) {
    axisMotionController_.moveToPositionInMicrometers(value);
}

uint32_t ZAxisController::getCurrentPositionInMicrometers() const {
    return axisMotionController_.getCurrentPositionInMicrometers();
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
    return axisMotionController_.isAtMinLimit();
}

void ZAxisController::moveToStartPosition() {
    axisMotionController_.moveToPositionInMicrometers(
        startPositionInMicrometers_
    );
}

bool ZAxisController::isAtStartPosition() const {
    return axisMotionController_.isAtPositionInMicrometers(
        startPositionInMicrometers_
    );
}

void ZAxisController::moveToEndPosition() {
    axisMotionController_.moveToPositionInMicrometers(
        endPositionInMicrometers_
    );
}

bool ZAxisController::isAtEndPosition() const {
    return axisMotionController_.isAtPositionInMicrometers(
        endPositionInMicrometers_
    );
}

void ZAxisController::setStartPositionInMicrometers(uint32_t value) {
    startPositionInMicrometers_ = value;
}

uint32_t ZAxisController::getStartPositionInMicrometers() const {
    return startPositionInMicrometers_;
}

void ZAxisController::setEndPositionInMicrometers(uint32_t value) {
    endPositionInMicrometers_ = value;
}

uint32_t ZAxisController::getEndPositionInMicrometers() const {
    return endPositionInMicrometers_;
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