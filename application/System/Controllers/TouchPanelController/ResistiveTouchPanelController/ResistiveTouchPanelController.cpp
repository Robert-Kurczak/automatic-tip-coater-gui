#include "ResistiveTouchPanelController.hpp"

namespace ATC {
static constexpr uint8_t SAMPLES_PER_READING_ = 10;

Vector2 ResistiveTouchPanelController::getFilteredRawPosition() {
    uint8_t samplesTaken = 0;
    uint32_t averageX = 0;
    uint32_t averageY = 0;

    while (resistiveTouchPanel_.isTouchDetected() &&
           samplesTaken < SAMPLES_PER_READING_) {
        averageX += resistiveTouchPanel_.readRawX();
        averageY += resistiveTouchPanel_.readRawY();
        samplesTaken++;
    }

    if (samplesTaken == 0) {
        return Vector2 {.x_ = 0, .y_ = 0};
    }

    averageX /= samplesTaken;
    averageY /= samplesTaken;

    return Vector2 {.x_ = uint16_t(averageX), .y_ = uint16_t(averageY)};
}

Vector2 ResistiveTouchPanelController::interpolateRawPosition(
    const Vector2& rawPosition
) const {
    const auto xNumerator =
        uint32_t(rawPosition.x_ - rawWorkingArea_.xStart_) *
        uint32_t(pixelResolution_.x_);

    const auto xDenominator =
        uint32_t(rawWorkingArea_.xEnd_ - rawWorkingArea_.xStart_);

    const auto yNumerator =
        uint32_t(rawPosition.y_ - rawWorkingArea_.yStart_) *
        uint32_t(pixelResolution_.y_);

    const auto yDenominator =
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
    uint16_t pressureTreshold,
    bool invertYAxis
) :
    resistiveTouchPanel_(resistiveTouchPanel),
    systemClock_(systemClock),
    rawWorkingArea_(rawWorkingArea),
    pixelResolution_(pixelResolution),
    pressureTreshold_(pressureTreshold),
    invertYAxis_(invertYAxis) {}

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

    Vector2 position = getFilteredRawPosition();
    position = interpolateRawPosition(position);

    if (invertYAxis_) {
        position.y_ = pixelResolution_.y_ - position.y_;
    }

    return position;
}
}