#include "Xpt2046TouchController.hpp"

namespace ATC {
uint16_t Xpt2046TouchController::transferReadCommand(uint8_t command) {
    pinout_.chipSelectPin_.setLow();

    uint8_t outputBuffer[2];

    spi_.sendData({&command, 1});
    spi_.receiveData(outputBuffer);

    pinout_.chipSelectPin_.setHigh();

    return ((outputBuffer[0] << 8) | outputBuffer[1]) >> 4;
}

Vector2 Xpt2046TouchController::getFilteredRawPosition() {
    uint8_t samplesTaken = 0;
    uint32_t averageX = 0;
    uint32_t averageY = 0;

    while (!pinout_.touchInterruptPin_.isHigh() && samplesTaken < 10) {
        averageX += transferReadCommand(READ_X_COMMAND_);
        averageY += transferReadCommand(READ_Y_COMMAND_);
        samplesTaken++;
    }

    averageX /= samplesTaken;
    averageY /= samplesTaken;

    return Vector2 {.x_ = uint16_t(averageX), .y_ = uint16_t(averageY)};
}

Vector2 Xpt2046TouchController::interpolateRawPosition(
    const Vector2& rawPosition
) {
    const uint32_t xNumerator =
        uint32_t(rawPosition.x_ - rawWorkingArea_.xStart_) *
        uint32_t(pixelResolution_.x_);

    const uint32_t xDenominator =
        uint32_t(rawWorkingArea_.xEnd_ - rawWorkingArea_.xStart_);

    const uint32_t yNumerator =
        uint32_t(rawPosition.y_ - rawWorkingArea_.yStart_) *
        uint32_t(pixelResolution_.y_);

    const uint32_t yDenominator =
        uint32_t(rawWorkingArea_.yEnd_ - rawWorkingArea_.yStart_);

    Vector2 interpolatedPosition {
        .x_ = uint16_t(xNumerator / xDenominator),
        .y_ = uint16_t(yNumerator / yDenominator)
    };

    return interpolatedPosition;
}

Xpt2046TouchController::Xpt2046TouchController(
    Xpt2046TouchControllerPinout& pinout,
    Spi& spi,
    Rectangle rawWorkingArea,
    Vector2 pixelResolution
) :
    pinout_(pinout),
    spi_(spi),
    rawWorkingArea_(rawWorkingArea),
    pixelResolution_(pixelResolution) {}

void Xpt2046TouchController::init() {
    pinout_.touchInterruptPin_.setInputMode();

    pinout_.chipSelectPin_.setOutputMode();
    pinout_.chipSelectPin_.setHigh();
}

bool Xpt2046TouchController::isPressed() {
    const bool isTouchDetected = !pinout_.touchInterruptPin_.isHigh();

    if (!isTouchDetected) {
        return false;
    }

    const bool isPressedEnough = readRawPressure() <= PRESSURE_TRESHOLD_;

    if (!wasTouched && isPressedEnough) {
        if (!debounceInProgress) {
            debounceInProgress = true;
            debounceStartTimestamp = HAL_GetTick();
        }

        if (HAL_GetTick() - debounceStartTimestamp >= DEBOUNCE_MS_) {
            wasTouched = true;
            debounceInProgress = false;
        }
    } else if (wasTouched && !isPressedEnough) {
        wasTouched = false;
    } else {
        debounceInProgress = false;
    }

    return wasTouched;
}

uint16_t Xpt2046TouchController::readRawPressure() {
    const uint16_t rawZ1Value = transferReadCommand(READ_Z1_COMMAND_);
    const uint16_t rawZ2Value = transferReadCommand(READ_Z2_COMMAND_);

    const uint16_t rawPressure = (rawZ2Value > rawZ1Value)
                                     ? (rawZ2Value - rawZ1Value)
                                     : (rawZ1Value - rawZ2Value);

    return rawPressure;
}

Vector2 Xpt2046TouchController::readPosition() {
    if (!isPressed()) {
        return Vector2 {.x_ = UINT16_MAX, .y_ = UINT16_MAX};
    }

    Vector2 rawPosition = getFilteredRawPosition();
    return interpolateRawPosition(rawPosition);
}
}