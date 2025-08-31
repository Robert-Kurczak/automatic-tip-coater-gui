#include <gui/yaxistestsscreen_screen/YAxisTestsScreenPresenter.hpp>
#include <gui/yaxistestsscreen_screen/YAxisTestsScreenView.hpp>

YAxisTestsScreenPresenter::YAxisTestsScreenPresenter(
    YAxisTestsScreenView& v
) :
    view(v) {}

void YAxisTestsScreenPresenter::activate() {}

void YAxisTestsScreenPresenter::deactivate() {}

void YAxisTestsScreenPresenter::handleYAxisTestTaskFinish(
    ATC::AxisTestResults results
) {
    view.resetFooterButtons();
    view.showTestResults(results);
}

void YAxisTestsScreenPresenter::startButtonPressed() {
    ATC::IConsumableTaskService<ATC::AxisTestResults>& yAxisTestTask =
        model->getSystemApi().tasks.yAxisTestTask;

    yAxisTestTask.schedule();
}

void YAxisTestsScreenPresenter::cancelButtonPressed() {
    ATC::ITaskControlService& taskControl =
        model->getSystemApi().tasks.taskControl;

    taskControl.cancelAll();
}