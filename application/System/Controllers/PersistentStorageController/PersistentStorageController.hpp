#pragma once

#include "IPersistentStorageController.hpp"
#include "PersistentData/AxisPersistentConfig.hpp"
#include "PersistentData/HeaterPersistentConfig.hpp"
#include "PersistentData/PersistentData.hpp"
#include "PersistentData/SpindlePersistentConfig.hpp"
#include "application/System/Drivers/LoggerSink/ILoggerSink.hpp"
#include "application/System/Drivers/PersistentStorage/IPersistentStorage.hpp"

#include <string_view>

namespace ATC {
class PersistentStorageController : public IPersistentStorageController {
private:
    ILoggerSink& loggerSink_;
    IPersistentStorage& persistentStorage_;

    PersistentData storedData_ {};

    void logAxisConfig(
        const AxisPersistentConfig& config,
        std::string_view axisName
    );
    void logSpindleConfig(const SpindlePersistentConfig& config);
    void logHeaterConfig(const HeaterPersistentConfig& config);
    void logPersistentData(const PersistentData& data);

    [[nodiscard]] uint32_t calculateDataChecksum(
        PersistentData data
    ) const;

    void createDefaultData();
    void updateStoredChecksum();
    void loadData();
    void validateStoredData();

public:
    PersistentStorageController(
        ILoggerSink& loggerSink,
        IPersistentStorage& persistentStorage
    );

    void init() override;

    void saveXAxisConfig(const AxisPersistentConfig& config) override;
    void saveYAxisConfig(const AxisPersistentConfig& config) override;
    void saveZAxisConfig(const AxisPersistentConfig& config) override;
    void saveSpindleConfig(
        const SpindlePersistentConfig& config
    ) override;
    void saveHeaterConfig(const HeaterPersistentConfig& config) override;

    [[nodiscard]] AxisPersistentConfig loadXAxisConfig() override;
    [[nodiscard]] AxisPersistentConfig loadYAxisConfig() override;
    [[nodiscard]] AxisPersistentConfig loadZAxisConfig() override;
    [[nodiscard]] SpindlePersistentConfig loadSpindleConfig() override;
    [[nodiscard]] HeaterPersistentConfig loadHeaterConfig() override;
};
}
