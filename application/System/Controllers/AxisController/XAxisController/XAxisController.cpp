#include "XAxisController.hpp"

namespace ATC {

static constexpr uint32_t HEATER_FRONT_POSITION_MULTIPLIER = 8;
static constexpr uint32_t HEATER_FRONT_POSITION_DIVIDER = 10;

XAxisController::XAxisController(
    ILoggerSink& loggerSink,
    IAxisMotionController& axisMotionController
) :
    loggerSink_(loggerSink),
    axisMotionController_(axisMotionController) {}

void XAxisController::init(const AxisPersistentConfig& config) {
    startPosition_ = config.startPosition;
    endPosition_ = config.endPosition;

    axisMotionController_.init();
}

void XAxisController::tick() {
    axisMotionController_.tick();
}

bool XAxisController::wasFaultReported() const {
    return axisMotionController_.wasFaultDetected();
}

void XAxisController::moveToPosition(uint32_t position) {
    axisMotionController_.moveTo(position);
}

uint32_t XAxisController::getCurrentPosition() const {
    return axisMotionController_.getCurrentPosition();
}

void XAxisController::moveToMinLimitPosition() {
    axisMotionController_.moveToMinLimitSwitch();
}

bool XAxisController::isAtMinLimitPosition() const {
    return axisMotionController_.isAtMinLimit();
}

void XAxisController::moveToMaxLimitPosition() {
    axisMotionController_.moveToMaxLimitSwitch();
}

bool XAxisController::isAtMaxLimitPosition() const {
    return axisMotionController_.isAtMaxLimit();
}

void XAxisController::moveToHomePosition() {
    axisMotionController_.homeAxis();
}

bool XAxisController::isAtHomePosition() const {
    return axisMotionController_.isAtMinLimit();
}

void XAxisController::moveToStartPosition() {
    axisMotionController_.moveTo(startPosition_);
}

bool XAxisController::isAtStartPosition() const {
    return axisMotionController_.isAtPosition(startPosition_);
}

void XAxisController::moveToEndPosition() {
    axisMotionController_.moveTo(endPosition_);
}

bool XAxisController::isAtEndPosition() const {
    return axisMotionController_.isAtPosition(endPosition_);
}

void XAxisController::moveToHeaterFrontPosition() {
    axisMotionController_.moveTo(heaterFrontPosition_);
}

bool XAxisController::isAtHeaterFrontPosition() const {
    return axisMotionController_.isAtPosition(heaterFrontPosition_);
}

void XAxisController::setStartPosition(uint32_t value) {
    startPosition_ = value;
}

uint32_t XAxisController::getStartPosition() const {
    return startPosition_;
}

void XAxisController::setEndPosition(uint32_t value) {
    endPosition_ = value;
    heaterFrontPosition_ =
        (endPosition_ / HEATER_FRONT_POSITION_DIVIDER) *
        HEATER_FRONT_POSITION_MULTIPLIER;
}

uint32_t XAxisController::getEndPosition() const {
    return endPosition_;
}

void XAxisController::setSpeedInMillimetersPerSecond(uint16_t value) {
    axisMotionController_.setMillimetersPerSecond(value);
}

uint16_t XAxisController::getSpeedInMillimetersPerSecond() const {
    return axisMotionController_.getMillimetersPerSecond();
}
}