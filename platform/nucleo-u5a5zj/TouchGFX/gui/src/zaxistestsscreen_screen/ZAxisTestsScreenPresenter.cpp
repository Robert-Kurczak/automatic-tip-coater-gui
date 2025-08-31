#include <gui/zaxistestsscreen_screen/ZAxisTestsScreenPresenter.hpp>
#include <gui/zaxistestsscreen_screen/ZAxisTestsScreenView.hpp>

ZAxisTestsScreenPresenter::ZAxisTestsScreenPresenter(
    ZAxisTestsScreenView& v
) :
    view(v) {}

void ZAxisTestsScreenPresenter::activate() {}

void ZAxisTestsScreenPresenter::deactivate() {}

void ZAxisTestsScreenPresenter::handleZAxisTestTaskFinish(
    ATC::AxisTestResults results
) {
    view.resetFooterButtons();
    view.showTestResults(results);
}

void ZAxisTestsScreenPresenter::startButtonPressed() {
    ATC::IConsumableTaskService<ATC::AxisTestResults>& zAxisTestTask =
        model->getSystemApi().tasks.zAxisTestTask;

    zAxisTestTask.schedule();
}

void ZAxisTestsScreenPresenter::cancelButtonPressed() {
    ATC::ITaskControlService& taskControl =
        model->getSystemApi().tasks.taskControl;

    taskControl.cancelAll();
}