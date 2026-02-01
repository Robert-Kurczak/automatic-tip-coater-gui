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
    startPositionInMicrometers_ = config.startPositionInMicrometers;
    endPositionInMicrometers_ = config.endPositionInMicrometers;

    axisMotionController_.init();
    axisMotionController_.setMillimetersPerSecond(
        config.speedInMillimetersPerSecond
    );
}

void XAxisController::tick() {
    axisMotionController_.tick();
}

bool XAxisController::wasFaultReported() const {
    return axisMotionController_.wasFaultDetected();
}

void XAxisController::moveToPositionInMicrometers(uint32_t value) {
    axisMotionController_.moveToPositionInMicrometers(value);
}

uint32_t XAxisController::getCurrentPositionInMicrometers() const {
    return axisMotionController_.getCurrentPositionInMicrometers();
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
    axisMotionController_.moveToPositionInMicrometers(
        startPositionInMicrometers_
    );
}

bool XAxisController::isAtStartPosition() const {
    return axisMotionController_.isAtPositionInMicrometers(
        startPositionInMicrometers_
    );
}

void XAxisController::moveToEndPosition() {
    axisMotionController_.moveToPositionInMicrometers(
        endPositionInMicrometers_
    );
}

bool XAxisController::isAtEndPosition() const {
    return axisMotionController_.isAtPositionInMicrometers(
        endPositionInMicrometers_
    );
}

void XAxisController::moveToHeaterFrontPosition() {
    axisMotionController_.moveToPositionInMicrometers(
        heaterFrontPositionInMicrometers_
    );
}

bool XAxisController::isAtHeaterFrontPosition() const {
    return axisMotionController_.isAtPositionInMicrometers(
        heaterFrontPositionInMicrometers_
    );
}

void XAxisController::setStartPositionInMicrometers(uint32_t value) {
    startPositionInMicrometers_ = value;
}

uint32_t XAxisController::getStartPositionInMicrometers() const {
    return startPositionInMicrometers_;
}

void XAxisController::setEndPositionInMicrometers(uint32_t value) {
    endPositionInMicrometers_ = value;

    heaterFrontPositionInMicrometers_ = value /
                                        HEATER_FRONT_POSITION_DIVIDER *
                                        HEATER_FRONT_POSITION_MULTIPLIER;
}

uint32_t XAxisController::getEndPositionInMicrometers() const {
    return endPositionInMicrometers_;
}

void XAxisController::setSpeedInMillimetersPerSecond(uint16_t value) {
    axisMotionController_.setMillimetersPerSecond(value);
}

uint16_t XAxisController::getSpeedInMillimetersPerSecond() const {
    return axisMotionController_.getMillimetersPerSecond();
}

void XAxisController::cancelMovement() {
    axisMotionController_.cancelMovement();
}
}