#include "Board.hpp"
#include "application/System/Logger/ILogger.hpp"

#include <source_location>

namespace ATC {
Board::Board(BoardDevices& devices, ILogger& logger) :
    devices_(devices),
    logger_(logger) {}

void Board::init() {
    devices_.xAxisController.init();
    devices_.yAxisController.init();
    devices_.zAxisController.init();
    devices_.rotator.init();
    devices_.heaterController.init();
    devices_.display.init();
    devices_.touchPanelController.init();
}

void Board::tick() {}

void Board::startCoatingTask() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
}

bool Board::isCoatingTaskDone() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
    return true;
}

bool Board::consumeCoatingTaskResult() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
    return true;
}

void Board::startCalibrationTask() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
}

bool Board::isCalibrationTaskDone() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
    return true;
}

bool Board::consumeCalibrationTaskResult() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
    return true;
}

void Board::startXAxisTestTask() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
}

bool Board::isXAxisTestTaskDone() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
    return true;
}

AxisTestResults Board::consumeXAxisTestTaskResult() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
    return AxisTestResults {
        .startLimitSwitchSuccess = true,
        .endLimitSwitchSuccess = false,
        .motorDriverSuccess = true
    };
}

void Board::startYAxisTestTask() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
}

bool Board::isYAxisTestTaskDone() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
    return true;
}

AxisTestResults Board::consumeYAxisTestTaskResult() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
    return AxisTestResults {
        .startLimitSwitchSuccess = true,
        .endLimitSwitchSuccess = false,
        .motorDriverSuccess = true
    };
}

void Board::startZAxisTestTask() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
}

bool Board::isZAxisTestTaskDone() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
    return true;
}

AxisTestResults Board::consumeZAxisTestTaskResult() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
    return AxisTestResults {
        .startLimitSwitchSuccess = true,
        .endLimitSwitchSuccess = false,
        .motorDriverSuccess = true
    };
}

void Board::startRotatorTestTask() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
}

bool Board::isRotatorTestTaskDone() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
    return true;
}

RotatorTestResults Board::consumeRotatorTestTaskResult() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
    return RotatorTestResults {.motorDriverSuccess = true};
}

void Board::startHeaterTestTask() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
}

bool Board::isHeaterTestTaskDone() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
    return true;
}

HeaterTestResults Board::consumeHeaterTestTaskResult() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
    return HeaterTestResults {.temperatureSuccess = true};
}

void Board::cancelCurrentTask() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
}

void Board::increaseXAxisStart() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
}

void Board::decreaseXAxisStart() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
}

void Board::saveXAxisStart() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
}

uint32_t Board::getXAxisStart() {
    return devices_.xAxisController.getStartPosition();
}

void Board::increaseXAxisEnd() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
}

void Board::decreaseXAxisEnd() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
}

void Board::saveXAxisEnd() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
}

uint32_t Board::getXAxisEnd() {
    return devices_.xAxisController.getEndPosition();
}

void Board::increaseXAxisSpeed() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
}

void Board::decreaseXAxisSpeed() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
}

void Board::saveXAxisSpeed() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
}

uint32_t Board::getXAxisSpeed() {
    return devices_.xAxisController.getSpeed();
}

void Board::increaseYAxisStart() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
}

void Board::decreaseYAxisStart() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
}

void Board::saveYAxisStart() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
}

uint32_t Board::getYAxisStart() {
    return devices_.yAxisController.getStartPosition();
}

void Board::increaseYAxisEnd() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
}

void Board::decreaseYAxisEnd() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
}

void Board::saveYAxisEnd() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
}

uint32_t Board::getYAxisEnd() {
    return devices_.yAxisController.getEndPosition();
}

void Board::increaseYAxisSpeed() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
}

void Board::decreaseYAxisSpeed() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
}

void Board::saveYAxisSpeed() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
}

uint32_t Board::getYAxisSpeed() {
    return devices_.yAxisController.getSpeed();
}

void Board::increaseZAxisStart() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
}

void Board::decreaseZAxisStart() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
}

void Board::saveZAxisStart() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
}

uint32_t Board::getZAxisStart() {
    return devices_.zAxisController.getStartPosition();
}

void Board::increaseZAxisEnd() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
}

void Board::decreaseZAxisEnd() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
}

void Board::saveZAxisEnd() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
}

uint32_t Board::getZAxisEnd() {
    return devices_.zAxisController.getEndPosition();
}

void Board::increaseZAxisSpeed() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
}

void Board::decreaseZAxisSpeed() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
}

void Board::saveZAxisSpeed() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
}

uint32_t Board::getZAxisSpeed() {
    return devices_.zAxisController.getSpeed();
}

// TODO change "Rotation" to "Rotator"
void Board::increaseRotationSpeed() {
    devices_.rotator.increaseSpeed();
}

void Board::decreaseRotationSpeed() {
    devices_.rotator.decreaseSpeed();
}

void Board::saveRotationSpeed() {
    devices_.rotator.saveSpeed();
}

uint32_t Board::getRotationSpeed() {
    return devices_.rotator.getSpeed();
}

void Board::setClockwiseRotation() {
    devices_.rotator.setDirectionClockwise();
}

void Board::setCounterClockwiseRotation() {
    devices_.rotator.setDirectionCounterClockwise();
}

void Board::saveRotationDirection() {
    devices_.rotator.setDirectionClockwise();
}

bool Board::isRotationClockwise() {
    return devices_.rotator.isDirectionClockwise();
}

void Board::increaseRotationTime() {
    return devices_.rotator.increaseRotationTime();
}

void Board::decreaseRotationTime() {
    return devices_.rotator.decreaseRotationTime();
}

void Board::saveRotationTime() {
    return devices_.rotator.saveRotationTime();
}

uint32_t Board::getRotationTime() {
    return devices_.rotator.getRotationTime();
}

void Board::setHeaterOn() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
}

void Board::setHeaterOff() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
}

void Board::saveHeaterState() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
}

bool Board::isHeaterOn() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
    return false;
}

void Board::increaseHeaterTemperature() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
}

void Board::decreaseHeaterTemperature() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
}

void Board::saveHeaterTemperature() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
}

uint32_t Board::getHeaterTemperature() {
    logger_.log(
        LOG_LEVEL::ERROR_LOG,
        std::source_location::current(),
        "Not implemented"
    );
    // TODO implement
    return 100;
}

void Board::drawOnDisplay(
    const std::span<const uint16_t>& frameBuffer,
    const Rectangle& window
) {
    devices_.display.draw(frameBuffer, window);
}

Vector2 Board::readTouchScreenPosition() {
    return devices_.touchPanelController.readPosition();
}
}
