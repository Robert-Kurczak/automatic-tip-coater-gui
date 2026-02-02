#include <gui/containers/SettingDisplay.hpp>

SettingDisplay::SettingDisplay() {}

void SettingDisplay::displayXAxisSettings(
    const ATC::AxisPersistentConfig& config
) {
    Unicode::snprintf(
        &xAxisStartValueBuffer[0],
        XAXISSTARTVALUE_SIZE,
        "%d",
        config.startPositionInMicrometers
    );
    xAxisStartValue.invalidate();

    Unicode::snprintf(
        &xAxisEndValueBuffer[0],
        XAXISENDVALUE_SIZE,
        "%d",
        config.endPositionInMicrometers
    );
    xAxisEndValue.invalidate();

    Unicode::snprintf(
        &xAxisSpeedValueBuffer[0],
        XAXISSPEEDVALUE_SIZE,
        "%d",
        config.speedInMillimetersPerSecond
    );
    xAxisSpeedValue.invalidate();
}

void SettingDisplay::displayYAxisSettings(
    const ATC::AxisPersistentConfig& config
) {
    Unicode::snprintf(
        &yAxisStartValueBuffer[0],
        YAXISSTARTVALUE_SIZE,
        "%d",
        config.startPositionInMicrometers
    );
    yAxisStartValue.invalidate();

    Unicode::snprintf(
        &yAxisEndValueBuffer[0],
        YAXISENDVALUE_SIZE,
        "%d",
        config.endPositionInMicrometers
    );
    yAxisEndValue.invalidate();

    Unicode::snprintf(
        &yAxisSpeedValueBuffer[0],
        YAXISSPEEDVALUE_SIZE,
        "%d",
        config.speedInMillimetersPerSecond
    );
    yAxisSpeedValue.invalidate();
}

void SettingDisplay::displayZAxisSettings(
    const ATC::AxisPersistentConfig& config
) {
    Unicode::snprintf(
        &zAxisStartValueBuffer[0],
        ZAXISSTARTVALUE_SIZE,
        "%d",
        config.startPositionInMicrometers
    );
    zAxisStartValue.invalidate();

    Unicode::snprintf(
        &zAxisEndValueBuffer[0],
        ZAXISENDVALUE_SIZE,
        "%d",
        config.endPositionInMicrometers
    );
    zAxisEndValue.invalidate();

    Unicode::snprintf(
        &zAxisSpeedValueBuffer[0],
        ZAXISSPEEDVALUE_SIZE,
        "%d",
        config.speedInMillimetersPerSecond
    );
    zAxisSpeedValue.invalidate();
}

void SettingDisplay::displayHeaterSettings(
    const ATC::HeaterPersistentConfig& config
) {
    Unicode::snprintfFloat(
        &heaterTemperatureValueBuffer[0],
        HEATERTEMPERATUREVALUE_SIZE,
        "%.2f",
        config.targetTemperatureInCelsius
    );
    heaterTemperatureValue.invalidate();
}

void SettingDisplay::displaySpindleSettings(
    const ATC::SpindlePersistentConfig& config
) {
    Unicode::snprintf(
        &spindleSpeedValueBuffer[0],
        SPINDLESPEEDVALUE_SIZE,
        "%d",
        config.speedPercent
    );
    spindleSpeedValue.invalidate();

    Unicode::snprintf(
        &spindleDirectionValueBuffer[0],
        SPINDLEDIRECTIONVALUE_SIZE,
        config.isDirectionClockwise ? "CW" : "CCW"
    );
    spindleDirectionValue.invalidate();

    Unicode::snprintf(
        &spindleRotationTimeValueBuffer[0],
        SPINDLEROTATIONTIMEVALUE_SIZE,
        "%d",
        config.timedRotationInMillis
    );
    spindleRotationTimeValue.invalidate();
}

void SettingDisplay::initialize() {
    SettingDisplayBase::initialize();
}
