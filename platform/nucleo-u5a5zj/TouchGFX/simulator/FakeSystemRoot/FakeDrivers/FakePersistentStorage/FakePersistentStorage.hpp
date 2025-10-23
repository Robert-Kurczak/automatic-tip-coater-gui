#pragma once

#include "application/System/Drivers/PersistentStorage/IPersistentStorage.hpp"
#include "application/System/Drivers/Logger/ILogger.hpp"

#include <filesystem>
#include <stdint.h>

namespace ATC {
class FakePersistentStorage : public IPersistentStorage {
private:
    ILogger& logger_;
    const std::filesystem::path storageFilePath_;
    const uint32_t storageSize_;

public:
    FakePersistentStorage(
        ILogger& logger,
        const std::filesystem::path& storageFilePath,
        const uint32_t storageSize
    );

    virtual void init() override;

    virtual void read(
        uint32_t address,
        const std::span<uint8_t>& outputBuffer
    ) override;

    virtual void write(
        uint32_t address,
        const std::span<const uint8_t>& data
    ) override;
};
}