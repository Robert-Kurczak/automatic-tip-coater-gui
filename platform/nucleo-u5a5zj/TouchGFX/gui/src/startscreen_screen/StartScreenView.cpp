#include <gui/startscreen_screen/StartScreenView.hpp>

void StartScreenView::displaySettings() {
    settingDisplay.displayXAxisSettings(presenter->getXAxisConfig());
    settingDisplay.displayYAxisSettings(presenter->getYAxisConfig());
    settingDisplay.displayZAxisSettings(presenter->getZAxisConfig());
}

StartScreenView::StartScreenView() {}

void StartScreenView::setupScreen() {
    StartScreenViewBase::setupScreen();

    displaySettings();
}

void StartScreenView::tearDownScreen() {
    StartScreenViewBase::tearDownScreen();
}

void StartScreenView::startCoating() {
    presenter->startButtonPressed();
}

void StartScreenView::cancelCoating() {
    presenter->cancelButtonPressed();
}

void StartScreenView::resetFooterButtons() {
    startCancelFooter.resetState();
}
