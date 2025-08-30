#include <gui/yaxistestsscreen_screen/YAxisTestsScreenPresenter.hpp>
#include <gui/yaxistestsscreen_screen/YAxisTestsScreenView.hpp>

YAxisTestsScreenPresenter::YAxisTestsScreenPresenter(
    YAxisTestsScreenView& v
) :
    view(v) {}

void YAxisTestsScreenPresenter::activate() {
    yAxisTestTask = &model->getSystemApi().tasks.yAxisTestTask;
}

void YAxisTestsScreenPresenter::deactivate() {}

void YAxisTestsScreenPresenter::handleYAxisTestTaskFinish(
    ATC::AxisTestResults results
) {
    view.resetFooterButtons();
    view.showTestResults(results);
}

void YAxisTestsScreenPresenter::startButtonPressed() {
    yAxisTestTask->schedule();
}

void YAxisTestsScreenPresenter::cancelButtonPressed() {
    model->getSystemApi().tasks.taskControl.cancelAll();
}