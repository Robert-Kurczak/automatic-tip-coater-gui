#include <gui/xaxistestsscreen_screen/XAxisTestsScreenPresenter.hpp>
#include <gui/xaxistestsscreen_screen/XAxisTestsScreenView.hpp>

XAxisTestsScreenPresenter::XAxisTestsScreenPresenter(
    XAxisTestsScreenView& v
) :
    view(v) {}

void XAxisTestsScreenPresenter::activate() {}

void XAxisTestsScreenPresenter::deactivate() {}

void XAxisTestsScreenPresenter::handleXAxisTestTaskFinish(
    ATC::AxisTestResults results
) {
    view.resetFooterButtons();
    view.showTestResults(results);
}

void XAxisTestsScreenPresenter::startButtonPressed() {
    ATC::IConsumableTaskService<ATC::AxisTestResults>& xAxisTestTask =
        model->getSystemApi().tasks.xAxisTestTask;

    xAxisTestTask.schedule();
}

void XAxisTestsScreenPresenter::cancelButtonPressed() {
    ATC::ITaskControlService& taskControl =
        model->getSystemApi().tasks.taskControl;

    taskControl.cancelAll();
}