#pragma once

#include "IXAxisController.hpp"
#include "application/System/Drivers/LoggerSink/ILoggerSink.hpp"

#include <cstdint>

namespace ATC {
class XAxisController : public IXAxisController {
private:
    ILoggerSink& loggerSink_;

    uint32_t startPosition_ = 0;
    uint32_t endPosition_ = 0;
    uint32_t speed_ = 0;

public:
    XAxisController(ILoggerSink& loggerSink);

    void init(const AxisPersistentConfig& config) override;
    void tick() override;

    [[nodiscard]] bool wasFaultReported() const override;

    void moveToPosition(uint32_t position) override;
    [[nodiscard]] uint32_t getCurrentPosition() const override;

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

    void moveToHeaterFrontPosition() override;
    [[nodiscard]] bool isAtHeaterFrontPosition() const override;

    void setStartPosition(uint32_t value) override;
    [[nodiscard]] uint32_t getStartPosition() const override;

    void setEndPosition(uint32_t value) override;
    [[nodiscard]] uint32_t getEndPosition() const override;

    void setSpeed(uint32_t value) override;
    [[nodiscard]] uint32_t getSpeed() const override;
};
}