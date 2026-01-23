#include "AxisInterruptService.hpp"

namespace ATC {
AxisInterruptService::AxisInterruptService(
    IAxisMotionController& axisMotionController
) :
    axisMotionController_(axisMotionController) {}

void AxisInterruptService::handleStepInterrupt() {
    axisMotionController_.handleStepPulseInterrupt();
}

void AxisInterruptService::handleMinLimitReachedInterrupt() {
    axisMotionController_.handleMinLimitSwitchInterrupt();
}

void AxisInterruptService::handleMaxLimitReachedInterrupt() {
    axisMotionController_.handleMaxLimitSwitchInterrupt();
}
}