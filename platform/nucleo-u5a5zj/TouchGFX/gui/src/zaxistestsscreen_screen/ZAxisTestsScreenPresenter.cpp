#include <gui/zaxistestsscreen_screen/ZAxisTestsScreenPresenter.hpp>
#include <gui/zaxistestsscreen_screen/ZAxisTestsScreenView.hpp>

ZAxisTestsScreenPresenter::ZAxisTestsScreenPresenter(
    ZAxisTestsScreenView& v
) :
    view(v) {}

void ZAxisTestsScreenPresenter::activate() {
    zAxisTestTask = &model->getSystemApi().tasks.zAxisTestTask;
}

void ZAxisTestsScreenPresenter::deactivate() {}

void ZAxisTestsScreenPresenter::handleZAxisTestTaskFinish(
    ATC::AxisTestResults results
) {
    view.resetFooterButtons();
    view.showTestResults(results);
}

void ZAxisTestsScreenPresenter::startButtonPressed() {
    zAxisTestTask->schedule();
}

void ZAxisTestsScreenPresenter::cancelButtonPressed() {
    model->getSystemApi().tasks.taskControl.cancelAll();
}