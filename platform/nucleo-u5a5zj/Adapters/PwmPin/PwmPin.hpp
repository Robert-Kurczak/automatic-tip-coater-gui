#pragma once

#include "main.h"
#include "application/System/Ports/IPwmPin.hpp"

namespace ATC {
class PwmPin : public IPwmPin {
private:
    TIM_HandleTypeDef& timerHandle_;
    const uint32_t channel_;

public:
    PwmPin(TIM_HandleTypeDef& timerHandle, uint32_t channel);

    virtual void setDutyCycle(uint8_t percent) override;
};
}
