#pragma once

#include "../ITouchController.hpp"
#include "application/Ports/IGpioPin.hpp"
#include "application/Spi/Spi.hpp"

namespace ATC {
struct Xpt2046TouchControllerPinout {
    IGpioPin& chipSelectPin_;
    IGpioPin& touchInterruptPin_;
};

class Xpt2046TouchController : public ITouchController {
private:
    static constexpr uint8_t READ_X_COMMAND_ = 0xD0;
    static constexpr uint8_t READ_Y_COMMAND_ = 0x90;
    static constexpr uint8_t READ_Z1_COMMAND_ = 0xB0;
    static constexpr uint8_t READ_Z2_COMMAND_ = 0xC0;

    static constexpr uint16_t PRESSURE_TRESHOLD_ = 1300;
    static constexpr uint8_t DEBOUNCE_MS_ = 20;

    Xpt2046TouchControllerPinout& pinout_;
    Spi& spi_;
    Rectangle rawWorkingArea_;
    const Vector2 pixelResolution_;

    bool wasTouched = false;
    bool debounceInProgress = false;
    uint32_t debounceStartTimestamp = 0;

    uint16_t transferReadCommand(uint8_t command);
    Vector2 getFilteredRawPosition();
    Vector2 interpolateRawPosition(const Vector2& rawPosition);

public:
    Xpt2046TouchController(
        Xpt2046TouchControllerPinout& pinout,
        Spi& spi,
        Rectangle rawWorkingArea,
        Vector2 pixelResolution
    );

    virtual void init() override;

    virtual bool isPressed() override;
    virtual uint16_t readRawPressure() override;
    virtual Vector2 readPosition() override;
};
}