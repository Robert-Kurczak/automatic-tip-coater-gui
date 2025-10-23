#include "FakePersistentStorage.hpp"

#include <fstream>
#include <vector>

namespace ATC {
FakePersistentStorage::FakePersistentStorage(
    ILogger& logger,
    const std::filesystem::path& storageFilePath,
    const uint32_t storageSize
) :
    logger_(logger),
    storageFilePath_(storageFilePath),
    storageSize_(storageSize) {}

void FakePersistentStorage::init() {
    if (std::filesystem::exists(storageFilePath_)) {
        return;
    }

    std::vector<uint8_t> initialContent(storageSize_, 1);

    std::filesystem::create_directories(storageFilePath_.parent_path());
    write(0, initialContent);
}

void FakePersistentStorage::read(
    uint32_t address,
    const std::span<uint8_t>& outputBuffer
) {
    if (address + outputBuffer.size() > storageSize_) {
        logger_.log(
            LOG_LEVEL::ERROR_LOG,
            std::source_location::current(),
            "Memory capacity exceeded while reading"
        );

        return;
    };

    std::ifstream binaryStream {storageFilePath_, std::ios::binary};

    binaryStream.seekg(address);
    binaryStream.read(
        reinterpret_cast<char*>(outputBuffer.data()), outputBuffer.size()
    );
}

void FakePersistentStorage::write(
    uint32_t address,
    const std::span<const uint8_t>& data
) {
    if (address + data.size() > storageSize_) {
        logger_.log(
            LOG_LEVEL::ERROR_LOG,
            std::source_location::current(),
            "Memory capacity exceeded while writing"
        );

        return;
    }

    std::ofstream binaryStream {storageFilePath_, std::ios::binary};

    binaryStream.seekp(address);
    binaryStream.write(
        reinterpret_cast<const char*>(data.data()), data.size()
    );
}
}