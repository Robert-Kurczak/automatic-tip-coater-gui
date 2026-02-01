#include <gui/calibratescreen_screen/CalibrateScreenView.hpp>

CalibrateScreenView::CalibrateScreenView() {}

void CalibrateScreenView::displaySettings() {
    settingDisplay.displayXAxisSettings(presenter->getXAxisConfig());
    settingDisplay.displayYAxisSettings(presenter->getYAxisConfig());
    settingDisplay.displayZAxisSettings(presenter->getZAxisConfig());
}

void CalibrateScreenView::setupScreen() {
    CalibrateScreenViewBase::setupScreen();
    displaySettings();
}

void CalibrateScreenView::tearDownScreen() {
    CalibrateScreenViewBase::tearDownScreen();
}

void CalibrateScreenView::startCalibration() {
    presenter->startButtonPressed();
}

void CalibrateScreenView::cancelCalibration() {
    presenter->cancelButtonPressed();
}

void CalibrateScreenView::resetFooterButtons() {
    startCancelFooter.resetState();
}