#pragma once

#include "IZAxisController.hpp"
#include "application/System/Controllers/AxisMotionController/IAxisMotionController.hpp"
#include "application/System/Drivers/LoggerSink/ILoggerSink.hpp"

#include <cstdint>

namespace ATC {
class ZAxisController : public IZAxisController {
private:
    ILoggerSink& loggerSink_;
    IAxisMotionController& axisMotionController_;

    uint32_t startPositionInMicrometers_ = 0;
    uint32_t endPositionInMicrometers_ = 0;

public:
    ZAxisController(
        ILoggerSink& loggerSink,
        IAxisMotionController& axisMotionController
    );

    void init(const AxisPersistentConfig& config) override;
    void tick() override;

    [[nodiscard]] bool wasFaultReported() const override;

    void moveToPositionInMicrometers(uint32_t value) override;
    [[nodiscard]] uint32_t
    getCurrentPositionInMicrometers() const override;

    void moveToMinLimitPosition() override;
    [[nodiscard]] bool isAtMinLimitPosition() const override;

    void moveToMaxLimitPosition() override;
    [[nodiscard]] bool isAtMaxLimitPosition() const override;

    void moveToHomePosition() override;
    [[nodiscard]] bool isAtHomePosition() const override;

    void moveToStartPosition() override;
    [[nodiscard]] bool isAtStartPosition() const override;

    void moveToEndPosition() override;
    [[nodiscard]] bool isAtEndPosition() const override;

    void setStartPositionInMicrometers(uint32_t value) override;
    [[nodiscard]] uint32_t getStartPositionInMicrometers() const override;

    void setEndPositionInMicrometers(uint32_t value) override;
    [[nodiscard]] uint32_t getEndPositionInMicrometers() const override;

    void setSpeedInMillimetersPerSecond(uint16_t value) override;
    [[nodiscard]] uint16_t getSpeedInMillimetersPerSecond() const override;

    void cancelMovement() override;
};
}