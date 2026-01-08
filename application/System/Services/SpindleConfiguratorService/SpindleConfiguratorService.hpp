#pragma once

#include "ISpindleConfiguratorService.hpp"
#include "application/System/Controllers/PersistentStorageController/IPersistentStorageController.hpp"
#include "application/System/Controllers/PersistentStorageController/PersistentData/SpindlePersistentConfig.hpp"
#include "application/System/Controllers/SpindleController/ISpindleController.hpp"

namespace ATC {
class SpindleConfiguratorService : public ISpindleConfiguratorService {
private:
    static constexpr uint32_t SHOWCASE_ROTATION_TIME_MILLIS_ = 3000;
    static constexpr uint8_t SPEED_PERCENT_STEP_ = 1;
    static constexpr uint32_t ROTATION_TIME_STEP_MILLIS_ = 500;

    IPersistentStorageController& persistentStorageController_;
    ISpindleController& spindleController_;

    SpindlePersistentConfig bufferedPersistentConfig_ {
        .speedPercentage = 0,
        .isDirectionClockwise = false,
        .timedRotationInMillis = 0
    };

public:
    SpindleConfiguratorService(
        IPersistentStorageController& persistentStorageController,
        ISpindleController& spindleController
    );

    SpindleConfiguratorService(const SpindleConfiguratorService&) =
        delete;

    SpindleConfiguratorService& operator=(
        const SpindleConfiguratorService&
    ) = delete;

    SpindleConfiguratorService(SpindleConfiguratorService&& other) =
        delete;

    SpindleConfiguratorService& operator=(
        SpindleConfiguratorService&& other
    ) = delete;

    ~SpindleConfiguratorService() = default;

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
};
}
