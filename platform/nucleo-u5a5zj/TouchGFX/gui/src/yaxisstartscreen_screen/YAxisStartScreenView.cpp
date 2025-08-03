#include <gui/yaxisstartscreen_screen/YAxisStartScreenView.hpp>

void YAxisStartScreenView::updateDisplayedValue() {
    const uint32_t position = presenter->getYAxisStart();
    axisStartSelector.setDisplayedValue(position);
}

YAxisStartScreenView::YAxisStartScreenView() {}

void YAxisStartScreenView::setupScreen() {
    YAxisStartScreenViewBase::setupScreen();
    updateDisplayedValue();
}

void YAxisStartScreenView::tearDownScreen() {
    YAxisStartScreenViewBase::tearDownScreen();
}

void YAxisStartScreenView::increaseButtonPressed() {
    presenter->increaseButtonPressed();
    updateDisplayedValue();
}

void YAxisStartScreenView::decreaseButtonPressed() {
    presenter->decreaseButtonPressed();
    updateDisplayedValue();
}

void YAxisStartScreenView::saveButtonPressed() {
    presenter->saveButtonPressed();
}