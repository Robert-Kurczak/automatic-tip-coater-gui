#pragma once

#include "application/System/Ports/IAdc.hpp"
#include "main.h"

namespace ATC {
class Adc : public IAdc {
private:
    ADC_HandleTypeDef& adcHandle_;
    const uint8_t resolutionBits_;
    const float referenceVoltage_;

public:
    struct ResolutionBits {
        uint8_t value;
    };
    struct ReferenceVoltage {
        float value;
    };

    Adc(ADC_HandleTypeDef& adcHandle,
        ResolutionBits resolutionBits,
        ReferenceVoltage referenceVoltage);

    void init() override;

    [[nodiscard]] uint8_t getResolutionBits() const override;
    [[nodiscard]] float getReferenceVoltage() const override;

    uint32_t readRaw() override;
};
}