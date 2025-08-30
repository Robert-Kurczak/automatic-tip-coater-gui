#include <gui/xaxistestsscreen_screen/XAxisTestsScreenPresenter.hpp>
#include <gui/xaxistestsscreen_screen/XAxisTestsScreenView.hpp>

XAxisTestsScreenPresenter::XAxisTestsScreenPresenter(
    XAxisTestsScreenView& v
) :
    view(v) {}

void XAxisTestsScreenPresenter::activate() {
    xAxisTestTask = &model->getSystemApi().tasks.xAxisTestTask;
}

void XAxisTestsScreenPresenter::deactivate() {}

void XAxisTestsScreenPresenter::handleXAxisTestTaskFinish(
    ATC::AxisTestResults results
) {
    view.resetFooterButtons();
    view.showTestResults(results);
}

void XAxisTestsScreenPresenter::startButtonPressed() {
    xAxisTestTask->schedule();
}

void XAxisTestsScreenPresenter::cancelButtonPressed() {
    model->getSystemApi().tasks.taskControl.cancelAll();
}