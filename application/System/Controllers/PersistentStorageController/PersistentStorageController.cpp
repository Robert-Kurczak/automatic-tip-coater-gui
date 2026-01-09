#include "PersistentStorageController.hpp"

#include "application/System/Config/DefaultPersistentConfig.hpp"
#include "application/System/Controllers/PersistentStorageController/PersistentData/SpindlePersistentConfig.hpp"
#include "application/Utils/Byte.hpp"
#include "application/Utils/Logger.hpp"

namespace ATC {
void PersistentStorageController::logAxisConfig(
    const AxisPersistentConfig& config,
    std::string_view axisName
) {
    log(loggerSink_,
        LogLevel::Debug,
        "=== {} axis config ===\n"
        "\tstart position: {}\n"
        "\tend position: {}\n"
        "\tspeed: {}\n",
        axisName,
        config.startPosition,
        config.endPosition,
        config.speed);
}

void PersistentStorageController::logSpindleConfig(
    const SpindlePersistentConfig& config
) {
    log(loggerSink_,
        LogLevel::Debug,
        "=== Spindle config ===\n"
        "\tspeed [%]: {}\n"
        "\tclockwise: {}\n"
        "\ttimed rotation [ms]: {}\n",
        config.speedPercentage,
        config.isDirectionClockwise,
        config.timedRotationInMillis);
}

void PersistentStorageController::logHeaterConfig(
    const HeaterPersistentConfig& config
) {
    log(loggerSink_,
        LogLevel::Debug,
        "=== Heater config ===\n"
        "\ttarget temperature [°C]: {}\n",
        config.targetTemperatureInCelsius);
}

void PersistentStorageController::logPersistentData(
    const PersistentData& data
) {
    logAxisConfig(data.xAxisConfig, "X");
    logAxisConfig(data.yAxisConfig, "Y");
    logAxisConfig(data.zAxisConfig, "Z");
    logSpindleConfig(data.spindleConfig);
    logHeaterConfig(data.heaterConfig);
    log(loggerSink_,
        LogLevel::Debug,
        "=== Metadata ===\n"
        "\tsignature: {}\n"
        "\tchecksum: {}\n",
        data.signature,
        data.checksum);
}

uint32_t PersistentStorageController::calculateDataChecksum(
    PersistentData data
) {
    data.checksum = 0;

    uint32_t calculatedChecksum = 0;
    for (const uint8_t byte : toByteSpan(data)) {
        calculatedChecksum += byte;
    }

    return calculatedChecksum;
}

void PersistentStorageController::createDefaultData() {
    PersistentData defaultData {
        .xAxisConfig = DEFAULT_X_AXIS_CONFIG,
        .yAxisConfig = DEFAULT_Y_AXIS_CONFIG,
        .zAxisConfig = DEFAULT_Z_AXIS_CONFIG,
        .spindleConfig = DEFAULT_SPINDLE_CONFIG,
        .heaterConfig = DEFAULT_HEATER_CONFIG,
        .signature = PersistentData::EXPECTED_SIGNATURE,
        .checksum = 0,
    };
    defaultData.checksum = calculateDataChecksum(defaultData);

    persistentStorage_.write(0, toByteSpan(defaultData));
    storedData_ = defaultData;

    log(loggerSink_,
        LogLevel::Debug,
        "=== Created default persistent storage data ===");
    logPersistentData(storedData_);
}

void PersistentStorageController::loadData() {
    std::array<uint8_t, sizeof(PersistentData)> rawDataBuffer {};
    persistentStorage_.read(0, rawDataBuffer);

    storedData_ = fromByteSpan<PersistentData>(rawDataBuffer);

    log(loggerSink_,
        LogLevel::Debug,
        "=== Loaded persistent storage  ===");
    logPersistentData(storedData_);
}

void PersistentStorageController::updateStoredChecksum() {
    const uint32_t checksumAddress = offsetof(PersistentData, checksum);
    const uint32_t updatedChecksum = calculateDataChecksum(storedData_);

    storedData_.checksum = updatedChecksum;

    log(loggerSink_,
        LogLevel::Debug,
        "=== Updating persistent storage checksum ===\n"
        "\taddress: {}\n"
        "\tnew checksum: {}\n",
        checksumAddress,
        updatedChecksum);

    persistentStorage_.write(
        checksumAddress, toByteSpan(updatedChecksum)
    );
}

void PersistentStorageController::validateStoredData() {
    const bool isSignatureValid =
        storedData_.signature == PersistentData::EXPECTED_SIGNATURE;

    log(loggerSink_,
        LogLevel::Debug,
        "=== Validating persistent storage signature ===\n"
        "\tstored signature: {}\n"
        "\texpected signature {}\n"
        "\tmatch: {}\n",
        storedData_.signature,
        PersistentData::EXPECTED_SIGNATURE,
        isSignatureValid);

    const uint32_t expectedChecksum = calculateDataChecksum(storedData_);
    const bool isChecksumValid = storedData_.checksum == expectedChecksum;

    log(loggerSink_,
        LogLevel::Debug,
        "=== Validating persistent storage checksum ===\n"
        "\tstored checksum: {}\n"
        "\texpected checksum {}\n"
        "\tmatch: {}\n",
        storedData_.checksum,
        expectedChecksum,
        isChecksumValid);

    if (isSignatureValid && isChecksumValid) {
        return;
    }

    createDefaultData();
}

PersistentStorageController::PersistentStorageController(
    ILoggerSink& loggerSink,
    IPersistentStorage& persistentStorage
) :
    loggerSink_(loggerSink),
    persistentStorage_(persistentStorage) {}

void PersistentStorageController::init() {
    persistentStorage_.init();

    loadData();
    validateStoredData();
}

void PersistentStorageController::saveXAxisConfig(
    const AxisPersistentConfig& config
) {
    if (areBytesEqual(config, storedData_.xAxisConfig)) {
        return;
    }

    const uint32_t address = offsetof(PersistentData, xAxisConfig);
    storedData_.xAxisConfig = config;
    persistentStorage_.write(address, toByteSpan(config));

    updateStoredChecksum();

    log(loggerSink_,
        LogLevel::Debug,
        "=== Saved X axis config ===\n"
        "\taddress: {}\n",
        address);
    logAxisConfig(config, "X");
}

void PersistentStorageController::saveYAxisConfig(
    const AxisPersistentConfig& config
) {
    if (areBytesEqual(config, storedData_.yAxisConfig)) {
        return;
    }

    const uint32_t address = offsetof(PersistentData, yAxisConfig);
    storedData_.yAxisConfig = config;
    persistentStorage_.write(address, toByteSpan(config));

    updateStoredChecksum();

    log(loggerSink_,
        LogLevel::Debug,
        "=== Saved Y axis config ===\n"
        "\taddress: {}\n",
        address);
    logAxisConfig(config, "Y");
}

void PersistentStorageController::saveZAxisConfig(
    const AxisPersistentConfig& config
) {
    if (areBytesEqual(config, storedData_.zAxisConfig)) {
        return;
    }

    const uint32_t address = offsetof(PersistentData, zAxisConfig);
    storedData_.zAxisConfig = config;
    persistentStorage_.write(address, toByteSpan(config));
    updateStoredChecksum();

    log(loggerSink_,
        LogLevel::Debug,
        "=== Saved Z axis config ===\n"
        "\taddress: {}\n",
        address);
    logAxisConfig(config, "Z");
}

void PersistentStorageController::saveSpindleConfig(
    const SpindlePersistentConfig& config
) {
    if (areBytesEqual(config, storedData_.spindleConfig)) {
        return;
    }

    const uint32_t address = offsetof(PersistentData, spindleConfig);
    storedData_.spindleConfig = config;
    persistentStorage_.write(address, toByteSpan(config));

    updateStoredChecksum();

    log(loggerSink_,
        LogLevel::Debug,
        "=== Saved spindle config ===\n"
        "\taddress: {}\n",
        address);
    logSpindleConfig(config);
}

void PersistentStorageController::saveHeaterConfig(
    const HeaterPersistentConfig& config
) {
    if (areBytesEqual(config, storedData_.heaterConfig)) {
        return;
    }

    const uint32_t address = offsetof(PersistentData, heaterConfig);
    storedData_.heaterConfig = config;
    persistentStorage_.write(address, toByteSpan(config));

    updateStoredChecksum();

    log(loggerSink_,
        LogLevel::Debug,
        "=== Saved heater config ===\n"
        "\taddress: {}\n",
        address);
    logHeaterConfig(config);
}

AxisPersistentConfig PersistentStorageController::loadXAxisConfig() {
    std::array<uint8_t, sizeof(AxisPersistentConfig)> buffer {};

    persistentStorage_.read(
        offsetof(PersistentData, xAxisConfig), buffer
    );

    return fromByteSpan<AxisPersistentConfig>(buffer);
}

AxisPersistentConfig PersistentStorageController::loadYAxisConfig() {
    std::array<uint8_t, sizeof(AxisPersistentConfig)> buffer {};

    persistentStorage_.read(
        offsetof(PersistentData, yAxisConfig), buffer
    );

    return fromByteSpan<AxisPersistentConfig>(buffer);
}

AxisPersistentConfig PersistentStorageController::loadZAxisConfig() {
    std::array<uint8_t, sizeof(AxisPersistentConfig)> buffer {};

    persistentStorage_.read(
        offsetof(PersistentData, zAxisConfig), buffer
    );

    return fromByteSpan<AxisPersistentConfig>(buffer);
}

SpindlePersistentConfig PersistentStorageController::loadSpindleConfig() {
    std::array<uint8_t, sizeof(SpindlePersistentConfig)> buffer {};

    persistentStorage_.read(
        offsetof(PersistentData, spindleConfig), buffer
    );

    return fromByteSpan<SpindlePersistentConfig>(buffer);
}

HeaterPersistentConfig PersistentStorageController::loadHeaterConfig() {
    std::array<uint8_t, sizeof(HeaterPersistentConfig)> buffer {};

    persistentStorage_.read(
        offsetof(PersistentData, heaterConfig), buffer
    );

    return fromByteSpan<HeaterPersistentConfig>(buffer);
}
}