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
    model->startXAxisTestTask();
}

void XAxisTestsScreenPresenter::cancelButtonPressed() {
    model->cancelCurrentTask();
}