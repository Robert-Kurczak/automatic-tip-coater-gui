#pragma once

#include "IYAxisController.hpp"
#include "application/System/Controllers/AxisMotionController/IAxisMotionController.hpp"
#include "application/System/Drivers/LimitSwitch/ILimitSwitch.hpp"
#include "application/System/Drivers/LoggerSink/ILoggerSink.hpp"

#include <cstdint>

namespace ATC {
class YAxisController : public IYAxisController {
private:
    ILoggerSink& loggerSink_;
    IAxisMotionController& axisMotionController_;
    ILimitSwitch& tipLimitSwitch_;

    uint32_t startPositionInMicrometers_ = 0;
    uint32_t endPositionInMicrometers_ = 0;

    bool detectingTip_ = false;
    uint32_t coatingPositionInMicrometers_ = 0;

    void handleTipDetected();

public:
    YAxisController(
        ILoggerSink& loggerSink,
        IAxisMotionController& axisMotionController,
        ILimitSwitch& tipLimitSwitch
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

    void moveToDetectTip() override;
    [[nodiscard]] bool isTipDetected() const override;

    void moveToCoatingPosition() override;
    [[nodiscard]] bool isAtCoatingPosition() const override;

    void setStartPositionInMicrometers(uint32_t value) override;
    [[nodiscard]] uint32_t getStartPositionInMicrometers() const override;

    void setEndPositionInMicrometers(uint32_t value) override;
    [[nodiscard]] uint32_t getEndPositionInMicrometers() const override;

    void setSpeedInMillimetersPerSecond(uint16_t value) override;
    [[nodiscard]] uint16_t getSpeedInMillimetersPerSecond() const override;

    void cancelMovement() override;
};
}