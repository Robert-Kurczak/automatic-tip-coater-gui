#pragma once

#include "../ILimitSwitch.hpp"
#include "application/System//Ports/IGpioPin.hpp"
#include "application/System/Drivers/Common/ActiveLevel.hpp"

namespace ATC {
template<ActiveLevel LEVEL>
class GpioLimitSwitch : public ILimitSwitch {
private:
    IGpioPin& inputPin_;

public:
    GpioLimitSwitch(IGpioPin& inputPin) : inputPin_(inputPin) {}

    void init() override {
        if constexpr (LEVEL == ActiveLevel::ActiveHigh) {
            inputPin_.init(
                GpioMode::InterruptOnFallingEdge, GpioPull::PullUp
            );
        } else {
            inputPin_.init(
                GpioMode::InterruptOnRisingEdge, GpioPull::PullDown
            );
        }
    };

    [[nodiscard]] bool isActive() const override {
        if constexpr (LEVEL == ActiveLevel::ActiveHigh) {
            return inputPin_.isHigh();
        } else {
            return inputPin_.isLow();
        }
    }
};
}
