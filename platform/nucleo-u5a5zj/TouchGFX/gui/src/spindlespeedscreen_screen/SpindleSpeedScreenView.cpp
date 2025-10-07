#include <gui/spindlespeedscreen_screen/SpindleSpeedScreenView.hpp>

void SpindleSpeedScreenView::updateDisplayedValue() {
    const uint8_t speedPercent = presenter->getSpindleSpeedPercent();
    speedSelector.setDisplayedValue(speedPercent);
}

SpindleSpeedScreenView::SpindleSpeedScreenView() {}

void SpindleSpeedScreenView::setupScreen() {
    SpindleSpeedScreenViewBase::setupScreen();
    updateDisplayedValue();
}

void SpindleSpeedScreenView::tearDownScreen() {
    SpindleSpeedScreenViewBase::tearDownScreen();
}

void SpindleSpeedScreenView::resetConfigurator() {
    presenter->resetConfigurator();
}

void SpindleSpeedScreenView::increaseButtonPressed() {
    presenter->increaseButtonPressed();
    updateDisplayedValue();
}

void SpindleSpeedScreenView::decreaseButtonPressed() {
    presenter->decreaseButtonPressed();
    updateDisplayedValue();
}

void SpindleSpeedScreenView::saveButtonPressed() {
    presenter->saveButtonPressed();
}
