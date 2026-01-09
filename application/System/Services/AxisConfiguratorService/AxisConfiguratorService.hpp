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
        .startPosition = 0,
        .endPosition = 0,
        .speed = 0
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
    [[nodiscard]] uint32_t getStartPosition() const override;

    void showcaseEndPosition() override;
    void increaseEndPosition() override;
    void decreaseEndPosition() override;
    void saveEndPosition() override;
    [[nodiscard]] uint32_t getEndPosition() const override;

    void showcaseSpeed() override;
    void increaseSpeed() override;
    void decreaseSpeed() override;
    void saveSpeed() override;
    [[nodiscard]] uint32_t getSpeed() const override;
};
}
