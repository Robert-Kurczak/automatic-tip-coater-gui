#include <gui/containers/SettingDisplay.hpp>

SettingDisplay::SettingDisplay() {}

void SettingDisplay::displayXAxisSettings(
    const ATC::AxisPersistentConfig& config
) {
    Unicode::snprintf(
        xAxisStartValueBuffer,
        XAXISSTARTVALUE_SIZE,
        "%d",
        config.startPositionInMicrometers
    );
    xAxisStartValue.invalidate();

    Unicode::snprintf(
        xAxisEndValueBuffer,
        XAXISENDVALUE_SIZE,
        "%d",
        config.endPositionInMicrometers
    );
    xAxisEndValue.invalidate();

    Unicode::snprintf(
        xAxisSpeedValueBuffer,
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
        yAxisStartValueBuffer,
        YAXISSTARTVALUE_SIZE,
        "%d",
        config.startPositionInMicrometers
    );
    yAxisStartValue.invalidate();

    Unicode::snprintf(
        yAxisEndValueBuffer,
        YAXISENDVALUE_SIZE,
        "%d",
        config.endPositionInMicrometers
    );
    yAxisEndValue.invalidate();

    Unicode::snprintf(
        yAxisSpeedValueBuffer,
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
        zAxisStartValueBuffer,
        ZAXISSTARTVALUE_SIZE,
        "%d",
        config.startPositionInMicrometers
    );
    zAxisStartValue.invalidate();

    Unicode::snprintf(
        zAxisEndValueBuffer,
        ZAXISENDVALUE_SIZE,
        "%d",
        config.endPositionInMicrometers
    );
    zAxisEndValue.invalidate();

    Unicode::snprintf(
        zAxisSpeedValueBuffer,
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

void SettingDisplay::initialize() {
    SettingDisplayBase::initialize();
}
