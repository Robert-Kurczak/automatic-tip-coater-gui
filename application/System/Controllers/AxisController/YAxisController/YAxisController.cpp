#include "YAxisController.hpp"

static constexpr uint8_t COATING_POSITION_OFFSET_FACTOR_NUMERATOR = 95;
static constexpr uint8_t COATING_POSITION_OFFSET_FACTOR_DENOMINATOR = 100;

namespace ATC {
void YAxisController::handleTipDetected() {
    axisMotionController_.cancelMovement();

    const uint32_t detectedTipPosition =
        axisMotionController_.getCurrentPosition();
    coatingPosition_ = (detectedTipPosition /
                        COATING_POSITION_OFFSET_FACTOR_DENOMINATOR) *
                       COATING_POSITION_OFFSET_FACTOR_NUMERATOR;

    detectingTip_ = false;
}

YAxisController::YAxisController(
    ILoggerSink& loggerSink,
    IAxisMotionController& axisMotionController,
    ILimitSwitch& tipLimitSwitch
) :
    loggerSink_(loggerSink),
    axisMotionController_(axisMotionController),
    tipLimitSwitch_(tipLimitSwitch) {}

void YAxisController::init(const AxisPersistentConfig& config) {
    startPosition_ = config.startPosition;
    endPosition_ = config.endPosition;

    axisMotionController_.init();
    tipLimitSwitch_.init();
}

void YAxisController::tick() {
    axisMotionController_.tick();

    if (detectingTip_ && tipLimitSwitch_.isActive()) {
        handleTipDetected();
    }
}

bool YAxisController::wasFaultReported() const {
    return axisMotionController_.wasFaultDetected();
}

void YAxisController::moveToPosition(uint32_t position) {
    axisMotionController_.moveTo(position);
}

uint32_t YAxisController::getCurrentPosition() const {
    return axisMotionController_.getCurrentPosition();
}

void YAxisController::moveToMinLimitPosition() {
    axisMotionController_.moveToMinLimitSwitch();
}

bool YAxisController::isAtMinLimitPosition() const {
    return axisMotionController_.isAtMinLimit();
}

void YAxisController::moveToMaxLimitPosition() {
    axisMotionController_.moveToMaxLimitSwitch();
}

bool YAxisController::isAtMaxLimitPosition() const {
    return axisMotionController_.isAtMaxLimit();
}

void YAxisController::moveToHomePosition() {
    axisMotionController_.homeAxis();
}

bool YAxisController::isAtHomePosition() const {
    return axisMotionController_.isAtMinLimit();
}

void YAxisController::moveToStartPosition() {
    axisMotionController_.moveTo(startPosition_);
}

bool YAxisController::isAtStartPosition() const {
    return axisMotionController_.isAtPosition(startPosition_);
}

void YAxisController::moveToEndPosition() {
    axisMotionController_.moveTo(endPosition_);
}

bool YAxisController::isAtEndPosition() const {
    return axisMotionController_.isAtPosition(endPosition_);
}

void YAxisController::moveToDetectTip() {
    detectingTip_ = true;
    axisMotionController_.moveToMaxLimitSwitch();
}

bool YAxisController::isTipDetected() const {
    return tipLimitSwitch_.isActive();
}

void YAxisController::moveToCoatingPosition() {
    axisMotionController_.moveTo(coatingPosition_);
}

bool YAxisController::isAtCoatingPosition() const {
    return axisMotionController_.isAtPosition(coatingPosition_);
}

void YAxisController::setStartPosition(uint32_t value) {
    startPosition_ = value;
}

uint32_t YAxisController::getStartPosition() const {
    return startPosition_;
}

void YAxisController::setEndPosition(uint32_t value) {
    endPosition_ = value;
}

uint32_t YAxisController::getEndPosition() const {
    return endPosition_;
}

void YAxisController::setSpeedInMillimetersPerSecond(uint16_t value) {
    axisMotionController_.setMillimetersPerSecond(value);
}

uint16_t YAxisController::getSpeedInMillimetersPerSecond() const {
    return axisMotionController_.getMillimetersPerSecond();
}

void YAxisController::cancelMovement() {
    axisMotionController_.cancelMovement();
}
}