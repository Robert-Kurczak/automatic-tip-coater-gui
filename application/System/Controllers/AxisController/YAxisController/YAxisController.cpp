#include "YAxisController.hpp"

static constexpr uint8_t COATING_POSITION_OFFSET_FACTOR_NUMERATOR = 95;
static constexpr uint8_t COATING_POSITION_OFFSET_FACTOR_DENOMINATOR = 100;

namespace ATC {
void YAxisController::handleTipDetected() {
    axisMotionController_.cancelMovement();

    const uint32_t detectedTipPositionInMicrometers =
        axisMotionController_.getCurrentPositionInMicrometers();

    coatingPositionInMicrometers_ =
        (detectedTipPositionInMicrometers /
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
    startPositionInMicrometers_ = config.startPositionInMicrometers;
    endPositionInMicrometers_ = config.endPositionInMicrometers;

    axisMotionController_.init();
    axisMotionController_.setMillimetersPerSecond(
        config.speedInMillimetersPerSecond
    );

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

void YAxisController::moveToPositionInMicrometers(uint32_t value) {
    axisMotionController_.moveToPositionInMicrometers(value);
}

uint32_t YAxisController::getCurrentPositionInMicrometers() const {
    return axisMotionController_.getCurrentPositionInMicrometers();
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
    axisMotionController_.moveToPositionInMicrometers(
        startPositionInMicrometers_
    );
}

bool YAxisController::isAtStartPosition() const {
    return axisMotionController_.isAtPositionInMicrometers(
        startPositionInMicrometers_
    );
}

void YAxisController::moveToEndPosition() {
    axisMotionController_.moveToPositionInMicrometers(
        endPositionInMicrometers_
    );
}

bool YAxisController::isAtEndPosition() const {
    return axisMotionController_.isAtPositionInMicrometers(
        endPositionInMicrometers_
    );
}

void YAxisController::moveToDetectTip() {
    detectingTip_ = true;
    axisMotionController_.moveToMaxLimitSwitch();
}

bool YAxisController::isTipDetected() const {
    return tipLimitSwitch_.isActive();
}

void YAxisController::moveToCoatingPosition() {
    axisMotionController_.moveToPositionInMicrometers(
        coatingPositionInMicrometers_
    );
}

bool YAxisController::isAtCoatingPosition() const {
    return axisMotionController_.isAtPositionInMicrometers(
        coatingPositionInMicrometers_
    );
}

void YAxisController::setStartPositionInMicrometers(uint32_t value) {
    startPositionInMicrometers_ = value;
}

uint32_t YAxisController::getStartPositionInMicrometers() const {
    return startPositionInMicrometers_;
}

void YAxisController::setEndPositionInMicrometers(uint32_t value) {
    endPositionInMicrometers_ = value;
}

uint32_t YAxisController::getEndPositionInMicrometers() const {
    return endPositionInMicrometers_;
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