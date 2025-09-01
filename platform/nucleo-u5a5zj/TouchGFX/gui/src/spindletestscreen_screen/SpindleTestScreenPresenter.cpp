#include <gui/spindletestscreen_screen/SpindleTestScreenPresenter.hpp>
#include <gui/spindletestscreen_screen/SpindleTestScreenView.hpp>

SpindleTestScreenPresenter::SpindleTestScreenPresenter(
    SpindleTestScreenView& v
) :
    view(v) {}

void SpindleTestScreenPresenter::activate() {}

void SpindleTestScreenPresenter::deactivate() {}

void SpindleTestScreenPresenter::handleSpindleTestTaskFinish(
    ATC::SpindleTestResults results
) {
    view.resetFooterButtons();
    view.showTestResults(results);
}

void SpindleTestScreenPresenter::startButtonPressed() {
    ATC::IConsumableTaskService<ATC::SpindleTestResults>&
        spindleTestTask = model->getSystemApi().tasks.spindleTestTask;

    spindleTestTask.schedule();
}

void SpindleTestScreenPresenter::cancelButtonPressed() {
    ATC::ITaskControlService& taskControl =
        model->getSystemApi().tasks.taskControl;

    taskControl.cancelAll();
}