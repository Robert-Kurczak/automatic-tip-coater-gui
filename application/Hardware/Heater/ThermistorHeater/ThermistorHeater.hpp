#pragma once

#include "../IHeater.hpp"
#include "application/System/Logger/ILogger.hpp"

namespace ATC {
class ThermistorHeater : public IHeater {
private:
    ILogger& logger_;

public:
    ThermistorHeater(ILogger& logger);

    virtual void init() override;
    virtual void tick() override;

    virtual void startTestTask(HeaterTestTaskCallback callback) override;

    virtual void setOn() override;
    virtual void setOff() override;
    virtual void saveState() override;
    virtual bool isOn() override;

    virtual void increaseTemperature() override;
    virtual void decreaseTemperature() override;
    virtual void saveTemperature() override;
    virtual uint32_t getTemperature() override;
};
}