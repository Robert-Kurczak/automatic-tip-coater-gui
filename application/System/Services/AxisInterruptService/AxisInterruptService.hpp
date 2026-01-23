#pragma once

#include "IAxisInterruptService.hpp"
#include "application/System/Controllers/AxisMotionController/IAxisMotionController.hpp"

namespace ATC {
class AxisInterruptService : public IAxisInterruptService {
private:
    IAxisMotionController& axisMotionController_;

public:
    AxisInterruptService(IAxisMotionController& axisMotionController);

    void handleStepInterrupt() override;
    void handleMinLimitReachedInterrupt() override;
    void handleMaxLimitReachedInterrupt() override;
};
}