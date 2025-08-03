#include <gui/rotationspeedscreen_screen/RotationSpeedScreenView.hpp>

void RotationSpeedScreenView::updateDisplayedValue() {
    const uint32_t speed = presenter->getRotationSpeed();
    speedSelector.setDisplayedValue(speed);
}

RotationSpeedScreenView::RotationSpeedScreenView() {}

void RotationSpeedScreenView::setupScreen() {
    RotationSpeedScreenViewBase::setupScreen();
    updateDisplayedValue();
}

void RotationSpeedScreenView::tearDownScreen() {
    RotationSpeedScreenViewBase::tearDownScreen();
}

void RotationSpeedScreenView::increaseButtonPressed() {
    presenter->increaseButtonPressed();
    updateDisplayedValue();
}

void RotationSpeedScreenView::decreaseButtonPressed() {
    presenter->decreaseButtonPressed();
    updateDisplayedValue();
}

void RotationSpeedScreenView::saveButtonPressed() {
    presenter->saveButtonPressed();
}