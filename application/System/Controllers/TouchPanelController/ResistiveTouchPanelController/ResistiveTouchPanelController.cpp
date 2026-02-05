#include "ResistiveTouchPanelController.hpp"

namespace ATC {
static constexpr uint8_t SAMPLES_PER_READING = 10;

Vector2 ResistiveTouchPanelController::getFilteredRawPosition() {
    uint8_t samplesTaken = 0;
    uint32_t averageX = 0;
    uint32_t averageY = 0;

    while (resistiveTouchPanel_.isTouchDetected() &&
           samplesTaken < SAMPLES_PER_READING) {
        averageX += resistiveTouchPanel_.readRawX();
        averageY += resistiveTouchPanel_.readRawY();
        samplesTaken++;
    }

    if (samplesTaken == 0) {
        return Vector2 {.x = 0, .y = 0};
    }

    averageX /= samplesTaken;
    averageY /= samplesTaken;

    return Vector2 {.x = uint16_t(averageX), .y = uint16_t(averageY)};
}

Vector2 ResistiveTouchPanelController::interpolateRawPosition(
    const Vector2& rawPosition
) const {
    const auto xNumerator =
        uint32_t(rawPosition.x - parameters_.rawWorkingArea.xStart) *
        uint32_t(parameters_.pixelResolution.x);

    const auto xDenominator = uint32_t(
        parameters_.rawWorkingArea.xEnd -
        parameters_.rawWorkingArea.xStart
    );

    const auto yNumerator =
        uint32_t(rawPosition.y - parameters_.rawWorkingArea.yStart) *
        uint32_t(parameters_.pixelResolution.y);

    const auto yDenominator = uint32_t(
        parameters_.rawWorkingArea.yEnd -
        parameters_.rawWorkingArea.yStart
    );

    Vector2 interpolatedPosition {
        .x = uint16_t(xNumerator / xDenominator),
        .y = uint16_t(yNumerator / yDenominator)
    };

    return interpolatedPosition;
}

ResistiveTouchPanelController::ResistiveTouchPanelController(
    IResistiveTouchPanel& resistiveTouchPanel,
    ISystemClock& systemClock,
    ResistiveTouchPanelParameters parameters
) :
    resistiveTouchPanel_(resistiveTouchPanel),
    systemClock_(systemClock),
    parameters_(parameters) {}

void ResistiveTouchPanelController::init() {
    resistiveTouchPanel_.init();
}

bool ResistiveTouchPanelController::isPressed() {
    if (!resistiveTouchPanel_.isTouchDetected()) {
        return false;
    }

    const bool isPressedEnough =
        resistiveTouchPanel_.readRawZ() <= parameters_.pressureTreshold;

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
        return Vector2 {.x = UINT16_MAX, .y = UINT16_MAX};
    }

    Vector2 position = getFilteredRawPosition();
    position = interpolateRawPosition(position);

    if (parameters_.invertYAxis) {
        position.y = parameters_.pixelResolution.y - position.y;
    }

    return position;
}
}