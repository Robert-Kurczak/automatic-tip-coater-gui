#include <gui/zaxistestscreen_screen/ZAxisTestScreenPresenter.hpp>
#include <gui/zaxistestscreen_screen/ZAxisTestScreenView.hpp>

ZAxisTestScreenPresenter::ZAxisTestScreenPresenter(
    ZAxisTestScreenView& v
) :
    view(v) {}

void ZAxisTestScreenPresenter::activate() {}

void ZAxisTestScreenPresenter::deactivate() {}

void ZAxisTestScreenPresenter::handleZAxisTestTaskFinish(
    ATC::AxisTestResults results
) {
    view.resetFooterButtons();
    view.showTestResults(results);
}

void ZAxisTestScreenPresenter::startButtonPressed() {
    ATC::IConsumableTaskService<ATC::AxisTestResults>& zAxisTestTask =
        model->getSystemApi().tasks.zAxisTestTask;

    zAxisTestTask.schedule();
}

void ZAxisTestScreenPresenter::cancelButtonPressed() {
    ATC::ITaskControlService& taskControl =
        model->getSystemApi().tasks.taskControl;

    taskControl.cancelAll();
}