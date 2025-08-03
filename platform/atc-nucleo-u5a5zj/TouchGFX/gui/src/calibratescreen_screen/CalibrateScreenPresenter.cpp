#include <gui/calibratescreen_screen/CalibrateScreenPresenter.hpp>
#include <gui/calibratescreen_screen/CalibrateScreenView.hpp>

CalibrateScreenPresenter::CalibrateScreenPresenter(
    CalibrateScreenView& v
) :
    view(v) {}

void CalibrateScreenPresenter::activate() {}

void CalibrateScreenPresenter::deactivate() {}

void CalibrateScreenPresenter::handleCalibrationTaskFinish(
    bool wasSuccessful
) {
    view.resetFooterButtons();
}

void CalibrateScreenPresenter::startButtonPressed() {
    model->startCalibrationTask();
}

void CalibrateScreenPresenter::cancelButtonPressed() {
    model->cancelCurrentTask();
}
