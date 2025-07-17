#include <gui/xaxisspeedscreen_screen/XAxisSpeedScreenView.hpp>

void XAxisSpeedScreenView::updateDisplayedValue() {
    const uint32_t speed = presenter->getXAxisSpeed();
    axisSpeedSelector.setDisplayedValue(speed);
}

XAxisSpeedScreenView::XAxisSpeedScreenView() {}

void XAxisSpeedScreenView::setupScreen() {
    XAxisSpeedScreenViewBase::setupScreen();
    updateDisplayedValue();
}

void XAxisSpeedScreenView::tearDownScreen() {
    XAxisSpeedScreenViewBase::tearDownScreen();
}

void XAxisSpeedScreenView::increaseButtonPressed() {
    presenter->increaseButtonPressed();
    updateDisplayedValue();
}

void XAxisSpeedScreenView::decreaseButtonPressed() {
    presenter->decreaseButtonPressed();
    updateDisplayedValue();
}

void XAxisSpeedScreenView::saveButtonPressed() {
    presenter->saveButtonPressed();
}