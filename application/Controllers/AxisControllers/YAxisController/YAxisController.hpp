#pragma once

#include "IYAxisController.hpp"
#include "application/System/Logger/ILogger.hpp"

#include <functional>
#include <stdint.h>

namespace ATC {
class YAxisController : public IYAxisController {
private:
    ILogger& logger_;

    uint32_t startPosition_;
    uint32_t endPosition_;
    uint32_t speed_;

public:
    YAxisController(ILogger& logger);

    virtual void init() override;
    virtual void tick() override;

    virtual void moveToStartPosition() override;
    virtual bool isAtStartPosition() const override;

    virtual void moveToEndPosition() override;
    virtual bool isAtEndPosition() const override;

    virtual void moveToDetectTip() override;
    virtual bool isTipDetected() const override;

    virtual void moveToCoatingPosition() override;
    virtual bool isAtCoatingPosition() const override;

    virtual void setStartPosition(uint32_t value) override;
    virtual uint32_t getStartPosition() const override;

    virtual void setEndPosition(uint32_t value) override;
    virtual uint32_t getEndPosition() const override;

    virtual void setSpeed(uint32_t value) override;
    virtual uint32_t getSpeed() const override;
};
}