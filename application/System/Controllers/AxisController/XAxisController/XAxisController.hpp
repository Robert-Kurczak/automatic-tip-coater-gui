#pragma once

#include "IXAxisController.hpp"
#include "application/System/Drivers/LoggerSink/ILoggerSink.hpp"

#include <stdint.h>

namespace ATC {
class XAxisController : public IXAxisController {
private:
    ILoggerSink& loggerSink_;

    uint32_t startPosition_;
    uint32_t endPosition_;
    uint32_t speed_;

public:
    XAxisController(ILoggerSink& loggerSink);

    virtual void init(const AxisPersistentConfig& config) override;
    virtual void tick() override;

    virtual bool wasFaultReported() const override;

    virtual void moveToPosition(uint32_t position) override;
    virtual uint32_t getCurrentPosition() const override;

    virtual void moveToMinLimitPosition() override;
    virtual bool isAtMinLimitPosition() const override;

    virtual void moveToMaxLimitPosition() override;
    virtual bool isAtMaxLimitPosition() const override;

    virtual void moveToHomePosition() override;
    virtual bool isAtHomePosition() const override;

    virtual void moveToStartPosition() override;
    virtual bool isAtStartPosition() const override;

    virtual void moveToEndPosition() override;
    virtual bool isAtEndPosition() const override;

    virtual void moveToHeaterFrontPosition() override;
    virtual bool isAtHeaterFrontPosition() const override;

    virtual void setStartPosition(uint32_t value) override;
    virtual uint32_t getStartPosition() const override;

    virtual void setEndPosition(uint32_t value) override;
    virtual uint32_t getEndPosition() const override;

    virtual void setSpeed(uint32_t value) override;
    virtual uint32_t getSpeed() const override;
};
}