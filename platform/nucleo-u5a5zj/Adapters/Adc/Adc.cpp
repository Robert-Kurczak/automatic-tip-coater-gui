#include "Adc.hpp"

namespace ATC {

Adc::Adc(
    ADC_HandleTypeDef& adcHandle,
    ResolutionBits resolutionBits,
    ReferenceVoltage referenceVoltage
) :
    adcHandle_(adcHandle),
    resolutionBits_(resolutionBits.value),
    referenceVoltage_(referenceVoltage.value) {}

void Adc::init() {
    HAL_ADCEx_Calibration_Start(
        &adcHandle_, ADC_CALIB_OFFSET, ADC_SINGLE_ENDED
    );
}

[[nodiscard]] uint8_t Adc::getResolutionBits() const {
    return resolutionBits_;
}

[[nodiscard]] float Adc::getReferenceVoltage() const {
    return referenceVoltage_;
}

uint32_t Adc::readRaw() {
    HAL_ADC_Start(&adcHandle_);
    HAL_ADC_PollForConversion(&adcHandle_, HAL_MAX_DELAY);

    return HAL_ADC_GetValue(&adcHandle_);
}
}