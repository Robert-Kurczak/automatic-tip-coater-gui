#include <gui/yaxistestscreen_screen/YAxisTestScreenPresenter.hpp>
#include <gui/yaxistestscreen_screen/YAxisTestScreenView.hpp>

YAxisTestScreenPresenter::YAxisTestScreenPresenter(
    YAxisTestScreenView& v
) :
    view(v) {}

void YAxisTestScreenPresenter::activate() {}

void YAxisTestScreenPresenter::deactivate() {}

void YAxisTestScreenPresenter::handleYAxisTestTaskFinish(
    ATC::AxisTestResults results
) {
    view.resetFooterButtons();
    view.showTestResults(results);
}

void YAxisTestScreenPresenter::startButtonPressed() {
    ATC::IConsumableTaskService<ATC::AxisTestResults>& yAxisTestTask =
        model->getSystemApi().tasks.yAxisTestTask;

    yAxisTestTask.schedule();
}

void YAxisTestScreenPresenter::cancelButtonPressed() {
    ATC::ITaskControlService& taskControl =
        model->getSystemApi().tasks.taskControl;

    taskControl.cancelAll();
}