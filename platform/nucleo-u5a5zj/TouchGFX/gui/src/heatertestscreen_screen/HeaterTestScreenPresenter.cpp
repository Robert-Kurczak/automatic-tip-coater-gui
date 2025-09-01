#include <gui/heatertestscreen_screen/HeaterTestScreenPresenter.hpp>
#include <gui/heatertestscreen_screen/HeaterTestScreenView.hpp>

HeaterTestScreenPresenter::HeaterTestScreenPresenter(
    HeaterTestScreenView& v
) :
    view(v) {}

void HeaterTestScreenPresenter::activate() {}

void HeaterTestScreenPresenter::deactivate() {}

void HeaterTestScreenPresenter::handleHeaterTestTaskFinish(
    ATC::HeaterTestResults results
) {
    view.resetFooterButtons();
    view.showTestResults(results);
}

void HeaterTestScreenPresenter::startButtonPressed() {
    ATC::IConsumableTaskService<ATC::HeaterTestResults>& heaterTestTask =
        model->getSystemApi().tasks.heaterTestTask;

    heaterTestTask.schedule();
}

void HeaterTestScreenPresenter::cancelButtonPressed() {
    ATC::ITaskControlService& taskControl =
        model->getSystemApi().tasks.taskControl;

    taskControl.cancelAll();
}