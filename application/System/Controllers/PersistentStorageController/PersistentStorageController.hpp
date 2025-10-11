#pragma once

#include "IPersistentStorageController.hpp"
#include "PersistentData/AxisPersistentConfig.hpp"
#include "PersistentData/HeaterPersistentConfig.hpp"
#include "PersistentData/SpindlePersistentConfig.hpp"
#include "application/System/Drivers/PersistentStorage/IPersistentStorage.hpp"

namespace ATC {
class PersistentStorageController : public IPersistentStorageController {
private:
    struct PersistentData {
        static constexpr uint32_t EXPECTED_SIGNATURE = 0xDEADBEEF;

        AxisPersistentConfig xAxisConfig;
        AxisPersistentConfig yAxisConfig;
        AxisPersistentConfig zAxisConfig;
        SpindlePersistentConfig spindleConfig;
        HeaterPersistentConfig heaterConfig;
        uint32_t signature;
        uint32_t checksum;
    };

    IPersistentStorage& persistentStorage_;

    PersistentData storedData_;

    uint32_t calculateDataChecksum(PersistentData data) const;
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

    virtual AxisPersistentConfig loadXAxisConfig() override;
    virtual AxisPersistentConfig loadYAxisConfig() override;
    virtual AxisPersistentConfig loadZAxisConfig() override;
    virtual SpindlePersistentConfig loadSpindleConfig() override;
    virtual HeaterPersistentConfig loadHeaterConfig() override;
};
}