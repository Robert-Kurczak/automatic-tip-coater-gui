#pragma once

#include "../ITouchPanelController.hpp"
#include "application/Drivers/ResistiveTouchPanel/IResistiveTouchPanel.hpp"
#include "application/Ports/ISystemClock.hpp"

namespace ATC {
class ResistiveTouchPanelController : public ITouchPanelController {
private:
    static constexpr uint8_t DEBOUNCE_MS_ = 20;

    IResistiveTouchPanel& resistiveTouchPanel_;
    ISystemClock& systemClock_;
    Rectangle rawWorkingArea_;
    const Vector2 pixelResolution_;
    const uint16_t pressureTreshold_;

    bool wasTouched_ = false;
    bool debounceInProgress_ = false;
    uint32_t debounceStartTimestamp_ = 0;

    bool isPressed();
    Vector2 getFilteredRawPosition();
    Vector2 interpolateRawPosition(const Vector2& rawPosition);

public:
    ResistiveTouchPanelController(
        IResistiveTouchPanel& resistiveTouchPanel,
        ISystemClock& systemClock,
        Rectangle rawWorkingArea,
        Vector2 pixelResolution,
        uint16_t pressureTreshold
    );

    virtual void init() override;

    virtual Vector2 readPosition() override;
};
}