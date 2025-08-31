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
    ATC::IConsumableTaskService<bool>& calibrationTask =
        model->getSystemApi().tasks.calibrationTask;

    calibrationTask.schedule();
}

void CalibrateScreenPresenter::cancelButtonPressed() {
    ATC::ITaskControlService& taskControl =
        model->getSystemApi().tasks.taskControl;

    taskControl.cancelAll();
}
