#include <gui/calibratescreen_screen/CalibrateScreenPresenter.hpp>
#include <gui/calibratescreen_screen/CalibrateScreenView.hpp>

CalibrateScreenPresenter::CalibrateScreenPresenter(
    CalibrateScreenView& v
) :
    view(v) {}

void CalibrateScreenPresenter::activate() {
    calibrationTask = &model->getSystemApi().tasks.calibrationTask;
}

void CalibrateScreenPresenter::deactivate() {}

void CalibrateScreenPresenter::handleCalibrationTaskFinish(
    bool wasSuccessful
) {
    view.resetFooterButtons();
}

void CalibrateScreenPresenter::startButtonPressed() {
    calibrationTask->schedule();
}

void CalibrateScreenPresenter::cancelButtonPressed() {
    model->getSystemApi().tasks.taskControl.cancelAll();
}
