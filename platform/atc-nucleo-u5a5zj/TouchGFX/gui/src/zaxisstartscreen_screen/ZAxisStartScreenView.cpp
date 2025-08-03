#include <gui/zaxisstartscreen_screen/ZAxisStartScreenView.hpp>

void ZAxisStartScreenView::updateDisplayedValue() {
    const uint32_t position = presenter->getZAxisStart();
    axisStartSelector.setDisplayedValue(position);
}

ZAxisStartScreenView::ZAxisStartScreenView() {}

void ZAxisStartScreenView::setupScreen() {
    ZAxisStartScreenViewBase::setupScreen();
    updateDisplayedValue();
}

void ZAxisStartScreenView::tearDownScreen() {
    ZAxisStartScreenViewBase::tearDownScreen();
}

void ZAxisStartScreenView::increaseButtonPressed() {
    presenter->increaseButtonPressed();
    updateDisplayedValue();
}

void ZAxisStartScreenView::decreaseButtonPressed() {
    presenter->decreaseButtonPressed();
    updateDisplayedValue();
}

void ZAxisStartScreenView::saveButtonPressed() {
    presenter->saveButtonPressed();
}