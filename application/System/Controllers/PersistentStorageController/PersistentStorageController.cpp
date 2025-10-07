#include "PersistentStorageController.hpp"

#include "DefaultPersistentConfigProvider.hpp"
#include "application/Utils/Byte.hpp"

namespace ATC {
uint32_t PersistentStorageController::calculateDataChecksum(
    PersistentData data
) const {
    data.checksum = 0;

    uint32_t calculatedChecksum = 0;
    for (const uint8_t byte : toByteSpan(data)) {
        calculatedChecksum += byte;
    }

    return calculatedChecksum;
}

void PersistentStorageController::createDefaultData() {
    PersistentData defaultData {
        .xAxisConfig = DefaultPersistentConfigProvider::getXAxisConfig(),
        .yAxisConfig = DefaultPersistentConfigProvider::getYAxisConfig(),
        .zAxisConfig = DefaultPersistentConfigProvider::getZAxisConfig(),
        .spindleConfig =
            DefaultPersistentConfigProvider::getSpindleConfig(),
        .heaterConfig =
            DefaultPersistentConfigProvider::getHeaterConfig(),
        .signature = PersistentData::EXPECTED_SIGNATURE,
        .checksum = 0,
    };
    defaultData.checksum = calculateDataChecksum(defaultData);

    persistentStorage_.write(0, toByteSpan(defaultData));
    storedData_ = defaultData;
}

void PersistentStorageController::loadData() {
    std::array<uint8_t, sizeof(PersistentData)> rawDataBuffer {};
    persistentStorage_.read(0, rawDataBuffer);

    storedData_ = fromByteSpan<PersistentData>(rawDataBuffer);
}

void PersistentStorageController::updateStoredChecksum() {
    const uint32_t updatedChecksum = calculateDataChecksum(storedData_);

    storedData_.checksum = updatedChecksum;

    persistentStorage_.write(
        offsetof(PersistentData, checksum), toByteSpan(updatedChecksum)
    );
}

void PersistentStorageController::validateStoredData() {
    const bool isSignatureValid =
        storedData_.signature == PersistentData::EXPECTED_SIGNATURE;

    const bool isChecksumValid =
        storedData_.checksum == calculateDataChecksum(storedData_);

    if (isSignatureValid && isChecksumValid) {
        return;
    }

    createDefaultData();
}

PersistentStorageController::PersistentStorageController(
    IPersistentStorage& persistentStorage
) :
    persistentStorage_(persistentStorage) {}

void PersistentStorageController::init() {
    loadData();
    validateStoredData();
}

void PersistentStorageController::saveXAxisConfig(
    const AxisConfig& config
) {
    if (areBytesEqual(config, storedData_.xAxisConfig)) {
        return;
    }

    storedData_.xAxisConfig = config;

    persistentStorage_.write(
        offsetof(PersistentData, xAxisConfig), toByteSpan(config)
    );

    updateStoredChecksum();
}

void PersistentStorageController::saveYAxisConfig(
    const AxisConfig& config
) {
    if (areBytesEqual(config, storedData_.yAxisConfig)) {
        return;
    }

    storedData_.yAxisConfig = config;

    persistentStorage_.write(
        offsetof(PersistentData, yAxisConfig), toByteSpan(config)
    );

    updateStoredChecksum();
}

void PersistentStorageController::saveZAxisConfig(
    const AxisConfig& config
) {
    if (areBytesEqual(config, storedData_.zAxisConfig)) {
        return;
    }

    storedData_.zAxisConfig = config;

    persistentStorage_.write(
        offsetof(PersistentData, zAxisConfig), toByteSpan(config)
    );

    updateStoredChecksum();
}

void PersistentStorageController::saveSpindleConfig(
    const SpindleConfig& config
) {
    if (areBytesEqual(config, storedData_.spindleConfig)) {
        return;
    }

    storedData_.spindleConfig = config;

    persistentStorage_.write(
        offsetof(PersistentData, spindleConfig), toByteSpan(config)
    );

    updateStoredChecksum();
}

void PersistentStorageController::saveHeaterConfig(
    const HeaterConfig& config
) {
    if (areBytesEqual(config, storedData_.heaterConfig)) {
        return;
    }

    storedData_.heaterConfig = config;

    persistentStorage_.write(
        offsetof(PersistentData, heaterConfig), toByteSpan(config)
    );

    updateStoredChecksum();
}
}