#pragma once

#include "AxisConfiguratorParameters.hpp"
#include "IAxisConfiguratorService.hpp"
#include "application/System/Controllers/AxisController/IAxisController.hpp"
#include "application/System/Controllers/PersistentStorageController/IPersistentStorageController.hpp"
#include "application/System/Controllers/PersistentStorageController/PersistentData/AxisPersistentConfig.hpp"

namespace ATC {
class AxisConfiguratorService : public IAxisConfiguratorService {
protected:
    virtual void saveConfigToPersistentMemory() = 0;

    IPersistentStorageController& getPersistentStorageController();
    AxisPersistentConfig& getBufferedPersistentConfig();

private:
    IPersistentStorageController& persistentStorageController_;
    IAxisController& axisController_;

    const AxisConfiguratorParameters parameters_;

    AxisPersistentConfig bufferedPersistentConfig_ {
        .startPositionInMicrometers = 0,
        .endPositionInMicrometers = 0,
        .speedInMillimetersPerSecond = 0
    };

public:
    AxisConfiguratorService(
        IPersistentStorageController& persistentStorageController,
        IAxisController& axisController,
        const AxisConfiguratorParameters& parameters
    );

    void resetBufferedConfig() override;

    void showcaseStartPosition() override;
    void increaseStartPosition() override;
    void decreaseStartPosition() override;
    void saveStartPosition() override;
    [[nodiscard]] uint32_t getStartPositionInMicrometers() const override;

    void showcaseEndPosition() override;
    void increaseEndPosition() override;
    void decreaseEndPosition() override;
    void saveEndPosition() override;
    [[nodiscard]] uint32_t getEndPositionInMicrometers() const override;

    void showcaseSpeed() override;
    void increaseSpeed() override;
    void decreaseSpeed() override;
    void saveSpeed() override;
    [[nodiscard]] uint32_t getSpeedInMillimetersPerSecond() const override;

    [[nodiscard]] AxisPersistentConfig getStoredConfig() const override;
};
}
