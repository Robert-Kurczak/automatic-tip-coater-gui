#include <gui/xaxistestscreen_screen/XAxisTestScreenPresenter.hpp>
#include <gui/xaxistestscreen_screen/XAxisTestScreenView.hpp>

XAxisTestScreenPresenter::XAxisTestScreenPresenter(
    XAxisTestScreenView& v
) :
    view(v) {}

void XAxisTestScreenPresenter::activate() {}

void XAxisTestScreenPresenter::deactivate() {}

void XAxisTestScreenPresenter::handleXAxisTestTaskFinish(
    ATC::AxisTestResults results
) {
    view.resetFooterButtons();
    view.showTestResults(results);
}

void XAxisTestScreenPresenter::startButtonPressed() {
    ATC::IConsumableTaskService<ATC::AxisTestResults>& xAxisTestTask =
        model->getSystemApi().tasks.xAxisTestTask;

    xAxisTestTask.schedule();
}

void XAxisTestScreenPresenter::cancelButtonPressed() {
    ATC::ITaskControlService& taskControl =
        model->getSystemApi().tasks.taskControl;

    taskControl.cancelAll();
}