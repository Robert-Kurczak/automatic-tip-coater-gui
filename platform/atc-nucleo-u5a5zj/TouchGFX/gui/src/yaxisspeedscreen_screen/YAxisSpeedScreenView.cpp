#include <gui/yaxisspeedscreen_screen/YAxisSpeedScreenView.hpp>

void YAxisSpeedScreenView::updateDisplayedValue() {
    const uint32_t speed = presenter->getYAxisSpeed();
    axisSpeedSelector.setDisplayedValue(speed);
}

YAxisSpeedScreenView::YAxisSpeedScreenView() {}

void YAxisSpeedScreenView::setupScreen() {
    YAxisSpeedScreenViewBase::setupScreen();
    updateDisplayedValue();
}

void YAxisSpeedScreenView::tearDownScreen() {
    YAxisSpeedScreenViewBase::tearDownScreen();
}

void YAxisSpeedScreenView::increaseButtonPressed() {
    presenter->increaseButtonPressed();
    updateDisplayedValue();
}

void YAxisSpeedScreenView::decreaseButtonPressed() {
    presenter->decreaseButtonPressed();
    updateDisplayedValue();
}

void YAxisSpeedScreenView::saveButtonPressed() {
    presenter->saveButtonPressed();
}