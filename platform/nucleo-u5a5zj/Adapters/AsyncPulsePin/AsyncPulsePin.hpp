#pragma once

#include "application/System/Ports/IAsyncPulsePin.hpp"
#include "main.h"

namespace ATC {
class AsyncPulsePin : public IAsyncPulsePin {
private:
    TIM_HandleTypeDef& timerHandle1MHz_;
    const uint32_t channel_;

public:
    AsyncPulsePin(TIM_HandleTypeDef& timerHandle1MHz, uint32_t channel);

    void enable() override;
    void disable() override;

    void setToggleMicroseconds(uint32_t value) override;
};
}