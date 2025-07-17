#include <gui/yaxisendscreen_screen/YAxisEndScreenView.hpp>

void YAxisEndScreenView::updateDisplayedValue() {
    const uint32_t position = presenter->getYAxisEnd();
    axisEndSelector.setDisplayedValue(position);
}

YAxisEndScreenView::YAxisEndScreenView() {}

void YAxisEndScreenView::setupScreen() {
    YAxisEndScreenViewBase::setupScreen();
    updateDisplayedValue();
}

void YAxisEndScreenView::tearDownScreen() {
    YAxisEndScreenViewBase::tearDownScreen();
}

void YAxisEndScreenView::increaseButtonPressed() {
    presenter->increaseButtonPressed();
    updateDisplayedValue();
}

void YAxisEndScreenView::decreaseButtonPressed() {
    presenter->decreaseButtonPressed();
    updateDisplayedValue();
}

void YAxisEndScreenView::saveButtonPressed() {
    presenter->saveButtonPressed();
}