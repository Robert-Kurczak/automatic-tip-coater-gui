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
        XAXISSTARTVALUE_SIZE,
        "%d",
        config.startPositionInMicrometers
    );
    yAxisStartValue.invalidate();

    Unicode::snprintf(
        yAxisEndValueBuffer,
        XAXISENDVALUE_SIZE,
        "%d",
        config.endPositionInMicrometers
    );
    yAxisEndValue.invalidate();

    Unicode::snprintf(
        yAxisSpeedValueBuffer,
        XAXISSPEEDVALUE_SIZE,
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
        XAXISSTARTVALUE_SIZE,
        "%d",
        config.startPositionInMicrometers
    );
    zAxisStartValue.invalidate();

    Unicode::snprintf(
        zAxisEndValueBuffer,
        XAXISENDVALUE_SIZE,
        "%d",
        config.endPositionInMicrometers
    );
    zAxisEndValue.invalidate();

    Unicode::snprintf(
        zAxisSpeedValueBuffer,
        XAXISSPEEDVALUE_SIZE,
        "%d",
        config.speedInMillimetersPerSecond
    );
    zAxisSpeedValue.invalidate();
}

void SettingDisplay::initialize() {
    SettingDisplayBase::initialize();
}
