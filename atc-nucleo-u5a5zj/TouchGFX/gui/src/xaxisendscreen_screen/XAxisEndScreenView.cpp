#include <gui/xaxisendscreen_screen/XAxisEndScreenView.hpp>

void XAxisEndScreenView::updateDisplayedValue() {
    const uint32_t position = presenter->getXAxisEnd();
    axisEndSelector.setDisplayedValue(position);
}

XAxisEndScreenView::XAxisEndScreenView() {}

void XAxisEndScreenView::setupScreen() {
    XAxisEndScreenViewBase::setupScreen();
    updateDisplayedValue();
}

void XAxisEndScreenView::tearDownScreen() {
    XAxisEndScreenViewBase::tearDownScreen();
}

void XAxisEndScreenView::increaseButtonPressed() {
    presenter->increaseButtonPressed();
    updateDisplayedValue();
}

void XAxisEndScreenView::decreaseButtonPressed() {
    presenter->decreaseButtonPressed();
    updateDisplayedValue();
}

void XAxisEndScreenView::saveButtonPressed() {
    presenter->saveButtonPressed();
}