#include <gui/heaterstatescreen_screen/HeaterStateScreenView.hpp>

void HeaterStateScreenView::updateDisplayedValue() {
    const uint32_t isOn = presenter->isHeaterOn();
    heaterStateSelector.setStateOn(isOn);
}

HeaterStateScreenView::HeaterStateScreenView() {}

void HeaterStateScreenView::setupScreen() {
    HeaterStateScreenViewBase::setupScreen();
    updateDisplayedValue();
}

void HeaterStateScreenView::tearDownScreen() {
    HeaterStateScreenViewBase::tearDownScreen();
}

void HeaterStateScreenView::stateOffButtonPressed() {
    presenter->offButtonPressed();
    updateDisplayedValue();
}

void HeaterStateScreenView::stateOnButtonPressed() {
    presenter->onButtonPressed();
    updateDisplayedValue();
}

void HeaterStateScreenView::saveButtonPressed() {
    presenter->saveButtonPressed();
}