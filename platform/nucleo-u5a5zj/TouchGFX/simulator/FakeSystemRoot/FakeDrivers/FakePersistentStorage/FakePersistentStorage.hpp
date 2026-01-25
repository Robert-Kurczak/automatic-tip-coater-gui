#pragma once

#include "application/System/Drivers/LoggerSink/ILoggerSink.hpp"
#include "application/System/Drivers/PersistentStorage/IPersistentStorage.hpp"

#include <filesystem>
#include <stdint.h>

namespace ATC {
class FakePersistentStorage : public IPersistentStorage {
private:
    ILoggerSink& loggerSink_;
    const std::filesystem::path storageFilePath_;
    const uint32_t storageSize_;

public:
    FakePersistentStorage(
        ILoggerSink& loggerSink,
        const std::filesystem::path& storageFilePath,
        const uint32_t storageSize
    );

    virtual void init() override;

    virtual void read(
        uint16_t address,
        std::span<uint8_t> outputBuffer
    ) override;

    virtual void write(
        uint16_t address,
        std::span<uint8_t> data
    ) override;
};
}