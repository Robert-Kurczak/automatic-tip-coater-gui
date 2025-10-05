#include "PersistentStorageController.hpp"
#include "application/Utils/Byte.hpp"

namespace ATC {
uint32_t PersistentStorageController::calculateDataChecksum(
    const PersistentData& data
) {
    // TODO implement
    return 0;
}

void PersistentStorageController::createDefaultData() {
    PersistentData defaultData {};

    //
    defaultData.checksum = calculateDataChecksum(defaultData);

    // TODO implement
    storedData_ = defaultData;
    persistentStorage_.write(0, toByteSpan(defaultData));
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
    uint32_t calculatedChecksum = calculateDataChecksum(storedData_);

    if (calculatedChecksum != storedData_.checksum) {
        createDefaultData();
    }
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
    const AxisPersistentConfig& config
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
    const AxisPersistentConfig& config
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
    const AxisPersistentConfig& config
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
    const SpindlePersistentConfig& config
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
    const HeaterPersistentConfig& config
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