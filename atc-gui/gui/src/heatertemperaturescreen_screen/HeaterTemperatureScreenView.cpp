#include <gui/heatertemperaturescreen_screen/HeaterTemperatureScreenView.hpp>

static uint16_t savedTemperature = 0;

HeaterTemperatureScreenView::HeaterTemperatureScreenView()
{
    temperature = savedTemperature;
    temperatureSelector.setDisplayedValue(temperature);
}

void HeaterTemperatureScreenView::setupScreen()
{
    HeaterTemperatureScreenViewBase::setupScreen();
}

void HeaterTemperatureScreenView::tearDownScreen()
{
    HeaterTemperatureScreenViewBase::tearDownScreen();
}

void HeaterTemperatureScreenView::increaseButtonPressed()
{
    if (temperature <= maxTemperature - temperatureIncrement)
    {
        temperature += temperatureIncrement;
        temperatureSelector.setDisplayedValue(temperature);
    }
}

void HeaterTemperatureScreenView::decreaseButtonPressed()
{
    if (temperature >= temperatureIncrement)
    {
        temperature -= temperatureIncrement;
        temperatureSelector.setDisplayedValue(temperature);
    }
}

void HeaterTemperatureScreenView::saveButtonPressed()
{
    savedTemperature = temperature;
}