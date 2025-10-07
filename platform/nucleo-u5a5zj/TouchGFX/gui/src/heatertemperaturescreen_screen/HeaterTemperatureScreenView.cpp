#include <gui/heatertemperaturescreen_screen/HeaterTemperatureScreenView.hpp>

void HeaterTemperatureScreenView::updateDisplayedValue() {
    const uint32_t temperature = presenter->getHeaterTemperature();
    temperatureSelector.setDisplayedValue(temperature);
}

HeaterTemperatureScreenView::HeaterTemperatureScreenView() {}

void HeaterTemperatureScreenView::setupScreen() {
    HeaterTemperatureScreenViewBase::setupScreen();
    updateDisplayedValue();
}

void HeaterTemperatureScreenView::tearDownScreen() {
    HeaterTemperatureScreenViewBase::tearDownScreen();
}

void HeaterTemperatureScreenView::resetConfigurator() {
    presenter->resetConfigurator();
}

void HeaterTemperatureScreenView::increaseButtonPressed() {
    presenter->increaseButtonPressed();
    updateDisplayedValue();
}

void HeaterTemperatureScreenView::decreaseButtonPressed() {
    presenter->decreaseButtonPressed();
    updateDisplayedValue();
}

void HeaterTemperatureScreenView::saveButtonPressed() {
    presenter->saveButtonPressed();
}
