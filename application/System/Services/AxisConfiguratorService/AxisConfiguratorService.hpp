#pragma once

#include "IAxisConfiguratorService.hpp"
#include "application/System/Controllers/AxisController/IAxisController.hpp"
#include "application/System/Controllers/PersistentStorageController/IPersistentStorageController.hpp"
#include "application/System/Drivers/Logger/ILogger.hpp"

namespace ATC {
class AxisConfiguratorService : public IAxisConfiguratorService {
protected:
    IPersistentStorageController& persistentStorageController_;

    uint32_t bufferedStartPosition_ = 0;
    uint32_t bufferedEndPosition_ = 0;
    uint32_t bufferedSpeed_ = 0;

    virtual void saveConfigToPersistentMemory() = 0;

private:
    IAxisController& axisController_;

    const uint8_t positionStep_;
    const uint8_t speedStep_;
    const uint32_t speedShowcasePosition_;

public:
    AxisConfiguratorService(
        IPersistentStorageController& persistentStorageController,
        IAxisController& axisController,
        uint8_t positionStep,
        uint8_t speedStep,
        uint32_t speedShowcasePosition
    );

    virtual void resetBufferedConfig() override;

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
