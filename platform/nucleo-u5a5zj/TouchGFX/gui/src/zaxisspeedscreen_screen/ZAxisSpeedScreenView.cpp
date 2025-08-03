#include <gui/zaxisspeedscreen_screen/ZAxisSpeedScreenView.hpp>

void ZAxisSpeedScreenView::updateDisplayedValue() {
    const uint32_t speed = presenter->getZAxisSpeed();
    axisSpeedSelector.setDisplayedValue(speed);
}

ZAxisSpeedScreenView::ZAxisSpeedScreenView() {}

void ZAxisSpeedScreenView::setupScreen() {
    ZAxisSpeedScreenViewBase::setupScreen();
    updateDisplayedValue();
}

void ZAxisSpeedScreenView::tearDownScreen() {
    ZAxisSpeedScreenViewBase::tearDownScreen();
}

void ZAxisSpeedScreenView::increaseButtonPressed() {
    presenter->increaseButtonPressed();
    updateDisplayedValue();
}

void ZAxisSpeedScreenView::decreaseButtonPressed() {
    presenter->decreaseButtonPressed();
    updateDisplayedValue();
}

void ZAxisSpeedScreenView::saveButtonPressed() {
    presenter->saveButtonPressed();
}