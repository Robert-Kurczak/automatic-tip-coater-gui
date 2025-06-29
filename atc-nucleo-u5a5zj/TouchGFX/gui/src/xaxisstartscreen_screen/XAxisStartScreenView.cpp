#include <gui/xaxisstartscreen_screen/XAxisStartScreenView.hpp>

void XAxisStartScreenView::updateDisplayedValue() {
    const uint32_t position = presenter->getXAxisStart();
    axisStartSelector.setDisplayedValue(position);
}

XAxisStartScreenView::XAxisStartScreenView() {}

void XAxisStartScreenView::setupScreen() {
    XAxisStartScreenViewBase::setupScreen();
    updateDisplayedValue();
}

void XAxisStartScreenView::tearDownScreen() {
    XAxisStartScreenViewBase::tearDownScreen();
}

void XAxisStartScreenView::increaseButtonPressed() {
    presenter->increaseButtonPressed();
    updateDisplayedValue();
}

void XAxisStartScreenView::decreaseButtonPressed() {
    presenter->decreaseButtonPressed();
    updateDisplayedValue();
}

void XAxisStartScreenView::saveButtonPressed() {
    presenter->saveButtonPressed();
}