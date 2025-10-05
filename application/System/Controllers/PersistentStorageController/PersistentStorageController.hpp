#pragma once

#include "IPersistentStorageController.hpp"
#include "application/System/Drivers/PersistentStorage/IPersistentStorage.hpp"

namespace ATC {
class PersistentStorageController : public IPersistentStorageController {
private:
    struct PersistentData {
        uint32_t checksum;
        AxisPersistentConfig xAxisConfig;
        AxisPersistentConfig yAxisConfig;
        AxisPersistentConfig zAxisConfig;
        SpindlePersistentConfig spindleConfig;
        HeaterPersistentConfig heaterConfig;
    };

    IPersistentStorage& persistentStorage_;

    PersistentData storedData_;

    uint32_t calculateDataChecksum(const PersistentData& data);
    void createDefaultData();
    void updateStoredChecksum();
    void loadData();
    void validateStoredData();

public:
    PersistentStorageController(IPersistentStorage& persistentStorage);

    virtual void init() override;

    virtual void saveXAxisConfig(
        const AxisPersistentConfig& config
    ) override;

    virtual void saveYAxisConfig(
        const AxisPersistentConfig& config
    ) override;

    virtual void saveZAxisConfig(
        const AxisPersistentConfig& config
    ) override;

    virtual void saveSpindleConfig(
        const SpindlePersistentConfig& config
    ) override;

    virtual void saveHeaterConfig(
        const HeaterPersistentConfig& config
    ) override;
};
}