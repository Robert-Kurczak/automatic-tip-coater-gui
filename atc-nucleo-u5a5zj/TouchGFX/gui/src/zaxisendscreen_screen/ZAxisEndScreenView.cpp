#include <gui/zaxisendscreen_screen/ZAxisEndScreenView.hpp>

void ZAxisEndScreenView::updateDisplayedValue() {
    const uint32_t position = presenter->getZAxisEnd();
    axisEndSelector.setDisplayedValue(position);
}

ZAxisEndScreenView::ZAxisEndScreenView() {}

void ZAxisEndScreenView::setupScreen() {
    ZAxisEndScreenViewBase::setupScreen();
    updateDisplayedValue();
}

void ZAxisEndScreenView::tearDownScreen() {
    ZAxisEndScreenViewBase::tearDownScreen();
}

void ZAxisEndScreenView::increaseButtonPressed() {
    presenter->increaseButtonPressed();
    updateDisplayedValue();
}

void ZAxisEndScreenView::decreaseButtonPressed() {
    presenter->decreaseButtonPressed();
    updateDisplayedValue();
}

void ZAxisEndScreenView::saveButtonPressed() {
    presenter->saveButtonPressed();
}