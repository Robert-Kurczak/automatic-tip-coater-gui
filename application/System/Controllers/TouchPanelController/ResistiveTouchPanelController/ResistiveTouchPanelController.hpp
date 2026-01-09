#pragma once

#include "../ITouchPanelController.hpp"
#include "application/System/Drivers/ResistiveTouchPanel/IResistiveTouchPanel.hpp"
#include "application/System/Ports/ISystemClock.hpp"

namespace ATC {
class ResistiveTouchPanelController : public ITouchPanelController {
private:
    static constexpr uint8_t DEBOUNCE_MS_ = 20;

    IResistiveTouchPanel& resistiveTouchPanel_;
    ISystemClock& systemClock_;
    Rectangle rawWorkingArea_;
    const Vector2 pixelResolution_;
    const uint16_t pressureTreshold_;
    const bool invertYAxis_;

    bool wasTouched_ = false;
    bool debounceInProgress_ = false;
    uint32_t debounceStartTimestamp_ = 0;

    bool isPressed();
    Vector2 getFilteredRawPosition();
    Vector2 interpolateRawPosition(const Vector2& rawPosition) const;

public:
    ResistiveTouchPanelController(
        IResistiveTouchPanel& resistiveTouchPanel,
        ISystemClock& systemClock,
        Rectangle rawWorkingArea,
        Vector2 pixelResolution,
        uint16_t pressureTreshold,
        bool invertYAxis = false
    );

    void init() override;

    Vector2 readPosition() override;
};
}
