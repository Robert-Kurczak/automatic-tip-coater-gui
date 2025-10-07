#pragma once

#include "IPersistentStorageController.hpp"
#include "application/System/Drivers/PersistentStorage/IPersistentStorage.hpp"

namespace ATC {
class PersistentStorageController : public IPersistentStorageController {
private:
    struct PersistentData {
        static constexpr uint32_t EXPECTED_SIGNATURE = 0xDEADBEEF;

        AxisConfig xAxisConfig;
        AxisConfig yAxisConfig;
        AxisConfig zAxisConfig;
        SpindleConfig spindleConfig;
        HeaterConfig heaterConfig;
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

    virtual void saveXAxisConfig(const AxisConfig& config) override;
    virtual void saveYAxisConfig(const AxisConfig& config) override;
    virtual void saveZAxisConfig(const AxisConfig& config) override;
    virtual void saveSpindleConfig(const SpindleConfig& config) override;
    virtual void saveHeaterConfig(const HeaterConfig& config) override;
};
}