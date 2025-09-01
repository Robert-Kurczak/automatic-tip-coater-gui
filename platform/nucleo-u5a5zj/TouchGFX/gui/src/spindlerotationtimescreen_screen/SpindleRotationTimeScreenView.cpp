#include <gui/spindlerotationtimescreen_screen/SpindleRotationTimeScreenView.hpp>

void SpindleRotationTimeScreenView::updateDisplayedValue() {
    const uint32_t rotationTimeInMillis =
        presenter->getSpindleRotationTimeInMillis();

    timeSelector.setDisplayedValue(rotationTimeInMillis);
}

SpindleRotationTimeScreenView::SpindleRotationTimeScreenView() {}

void SpindleRotationTimeScreenView::setupScreen() {
    SpindleRotationTimeScreenViewBase::setupScreen();
    updateDisplayedValue();
}

void SpindleRotationTimeScreenView::tearDownScreen() {
    SpindleRotationTimeScreenViewBase::tearDownScreen();
}

void SpindleRotationTimeScreenView::increaseButtonPressed() {
    presenter->increaseButtonPressed();
    updateDisplayedValue();
}

void SpindleRotationTimeScreenView::decreaseButtonPressed() {
    presenter->decreaseButtonPressed();
    updateDisplayedValue();
}

void SpindleRotationTimeScreenView::saveButtonPressed() {
    presenter->saveButtonPressed();
}