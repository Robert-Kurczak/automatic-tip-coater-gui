#include "FakePersistentStorage.hpp"

#include "application/Utils/Logger.hpp"

#include <fstream>
#include <source_location>
#include <vector>

namespace ATC {
FakePersistentStorage::FakePersistentStorage(
    ILoggerSink& loggerSink,
    const std::filesystem::path& storageFilePath,
    const uint32_t storageSize
) :
    loggerSink_(loggerSink),
    storageFilePath_(storageFilePath),
    storageSize_(storageSize) {}

void FakePersistentStorage::init() {
    if (std::filesystem::exists(storageFilePath_)) {
        return;
    }

    log(loggerSink_, LogLevel::Debug, "Creating new storage file");

    const auto parentDirectory = storageFilePath_.parent_path();
    if (!parentDirectory.empty()) {
        std::filesystem::create_directories(parentDirectory);
    }

    const std::vector<char> initialContent(storageSize_, 1);

    std::ofstream binaryStream {storageFilePath_, std::ios::binary};
    binaryStream.write(initialContent.data(), initialContent.size());
}

void FakePersistentStorage::read(
    uint16_t address,
    std::span<uint8_t> outputBuffer
) {
    if (address + outputBuffer.size() > storageSize_) {
        log(loggerSink_,
            LogLevel::Error,
            std::source_location::current(),
            "Memory capacity exceeded while reading");

        return;
    };

    std::ifstream binaryStream(
        storageFilePath_, std::ios::binary | std::ios::in
    );

    binaryStream.seekg(address);
    binaryStream.read(
        reinterpret_cast<char*>(outputBuffer.data()), outputBuffer.size()
    );
}

void FakePersistentStorage::write(
    uint16_t address,
    std::span<uint8_t> data
) {
    if (address + data.size() > storageSize_) {
        log(loggerSink_,
            LogLevel::Error,
            std::source_location::current(),
            "Memory capacity exceeded while writing");

        return;
    }

    std::ofstream binaryStream {
        storageFilePath_,
        std::ios::binary | std::ios::in | std::ios::out | std::ios::ate
    };

    binaryStream.seekp(address);
    binaryStream.write(
        reinterpret_cast<const char*>(data.data()), data.size()
    );
}
}