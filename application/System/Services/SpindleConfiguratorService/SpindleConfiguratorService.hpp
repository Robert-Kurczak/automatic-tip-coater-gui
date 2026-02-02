#pragma once

#include "ISpindleConfiguratorService.hpp"
#include "SpindleConfiguratorParameters.hpp"
#include "application/System/Controllers/PersistentStorageController/IPersistentStorageController.hpp"
#include "application/System/Controllers/PersistentStorageController/PersistentData/SpindlePersistentConfig.hpp"
#include "application/System/Controllers/SpindleController/ISpindleController.hpp"

namespace ATC {
class SpindleConfiguratorService : public ISpindleConfiguratorService {
private:
    IPersistentStorageController& persistentStorageController_;
    ISpindleController& spindleController_;
    const SpindleConfiguratorParameters parameters_;

    SpindlePersistentConfig bufferedPersistentConfig_ {
        .speedPercent = 0,
        .isDirectionClockwise = false,
        .timedRotationInMillis = 0
    };

public:
    SpindleConfiguratorService(
        IPersistentStorageController& persistentStorageController,
        ISpindleController& spindleController,
        SpindleConfiguratorParameters parameters
    );

    void resetBufferedConfig() override;

    void showcaseRotation() override;

    void increaseSpeedPercent() override;
    void decreaseSpeedPercent() override;
    void saveSpeedPercent() override;
    [[nodiscard]] uint8_t getSpeedPercent() const override;

    void setDirectionClockwise() override;
    void setDirectionCounterClockwise() override;
    void saveDirection() override;
    [[nodiscard]] bool isDirectionClockwise() const override;

    void increaseRotationTimeInMillis() override;
    void decreaseRotationTimeInMillis() override;
    void saveRotationTimeInMillis() override;
    [[nodiscard]] uint32_t getRotationTimeInMillis() const override;

    [[nodiscard]] SpindlePersistentConfig getStoredConfig() const override;
};
}
