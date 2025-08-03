#include <gui/rotationtimescreen_screen/RotationTimeScreenView.hpp>

void RotationTimeScreenView::updateDisplayedValue() {
    const uint32_t time = presenter->getRotationTime();
    timeSelector.setDisplayedValue(time);
}

RotationTimeScreenView::RotationTimeScreenView() {}

void RotationTimeScreenView::setupScreen() {
    RotationTimeScreenViewBase::setupScreen();
    updateDisplayedValue();
}

void RotationTimeScreenView::tearDownScreen() {
    RotationTimeScreenViewBase::tearDownScreen();
}

void RotationTimeScreenView::increaseButtonPressed() {
    presenter->increaseButtonPressed();
    updateDisplayedValue();
}

void RotationTimeScreenView::decreaseButtonPressed() {
    presenter->decreaseButtonPressed();
    updateDisplayedValue();
}

void RotationTimeScreenView::saveButtonPressed() {
    presenter->saveButtonPressed();
}