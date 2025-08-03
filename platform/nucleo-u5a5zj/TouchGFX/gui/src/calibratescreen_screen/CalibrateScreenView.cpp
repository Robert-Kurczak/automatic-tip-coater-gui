#include <gui/calibratescreen_screen/CalibrateScreenView.hpp>

CalibrateScreenView::CalibrateScreenView() {}

void CalibrateScreenView::setupScreen() {
    CalibrateScreenViewBase::setupScreen();
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