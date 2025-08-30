#pragma once

#include "IAxisConfiguratorService.hpp"
#include "application/System/Controllers/AxisController/IAxisController.hpp"
#include "application/System/Drivers/Logger/ILogger.hpp"

namespace ATC {
class AxisConfiguratorService : public IAxisConfiguratorService {
private:
    ILogger& logger_;
    IAxisController& axisController_;

    const uint8_t positionStep_;
    const uint8_t speedStep_;

public:
    AxisConfiguratorService(
        ILogger& logger,
        IAxisController& axisController,
        uint8_t positionStep,
        uint8_t speedStep
    );

    virtual void showcaseStartPosition() override;
    virtual void increaseStartPosition() override;
    virtual void decreaseStartPosition() override;
    virtual void saveStartPosition() override;
    virtual uint32_t getStartPosition() const override;

    virtual void showcaseEndPosition() override;
    virtual void increaseEndPosition() override;
    virtual void decreaseEndPosition() override;
    virtual void saveEndPosition() override;
    virtual uint32_t getEndPosition() const override;

    virtual void showcaseSpeed() override;
    virtual void increaseSpeed() override;
    virtual void decreaseSpeed() override;
    virtual void saveSpeed() override;
    virtual uint32_t getSpeed() const override;
};
}