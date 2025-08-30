#include "ResistiveTouchPanelController.hpp"

namespace ATC {
Vector2 ResistiveTouchPanelController::getFilteredRawPosition() {
    uint8_t samplesTaken = 0;
    uint32_t averageX = 0;
    uint32_t averageY = 0;

    while (resistiveTouchPanel_.isTouchDetected() && samplesTaken < 10) {
        averageX += resistiveTouchPanel_.readRawX();
        averageY += resistiveTouchPanel_.readRawY();
        samplesTaken++;
    }

    averageX /= samplesTaken;
    averageY /= samplesTaken;

    return Vector2 {.x_ = uint16_t(averageX), .y_ = uint16_t(averageY)};
}

Vector2 ResistiveTouchPanelController::interpolateRawPosition(
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

ResistiveTouchPanelController::ResistiveTouchPanelController(
    IResistiveTouchPanel& resistiveTouchPanel,
    ISystemClock& systemClock,
    Rectangle rawWorkingArea,
    Vector2 pixelResolution,
    uint16_t pressureTreshold
) :
    resistiveTouchPanel_(resistiveTouchPanel),
    systemClock_(systemClock),
    rawWorkingArea_(rawWorkingArea),
    pixelResolution_(pixelResolution),
    pressureTreshold_(pressureTreshold) {}

void ResistiveTouchPanelController::init() {
    resistiveTouchPanel_.init();
}

bool ResistiveTouchPanelController::isPressed() {
    if (!resistiveTouchPanel_.isTouchDetected()) {
        return false;
    }

    const bool isPressedEnough =
        resistiveTouchPanel_.readRawZ() <= pressureTreshold_;

    if (!wasTouched_ && isPressedEnough) {
        if (!debounceInProgress_) {
            debounceStartTimestamp_ =
                systemClock_.getMillisecondsSinceStart();
            debounceInProgress_ = true;
        }

        const uint32_t debounceMillisPassed =
            systemClock_.getMillisecondsSinceStart() -
            debounceStartTimestamp_;

        if (debounceMillisPassed >= DEBOUNCE_MS_) {
            wasTouched_ = true;
            debounceInProgress_ = false;
        }
    } else if (wasTouched_ && !isPressedEnough) {
        wasTouched_ = false;
    } else {
        debounceInProgress_ = false;
    }

    return wasTouched_;
}

Vector2 ResistiveTouchPanelController::readPosition() {
    if (!isPressed()) {
        return Vector2 {.x_ = UINT16_MAX, .y_ = UINT16_MAX};
    }

    Vector2 rawPosition = getFilteredRawPosition();
    return interpolateRawPosition(rawPosition);
}
}