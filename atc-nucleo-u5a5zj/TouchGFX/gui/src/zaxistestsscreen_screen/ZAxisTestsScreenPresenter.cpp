#include <gui/zaxistestsscreen_screen/ZAxisTestsScreenPresenter.hpp>
#include <gui/zaxistestsscreen_screen/ZAxisTestsScreenView.hpp>

ZAxisTestsScreenPresenter::ZAxisTestsScreenPresenter(
    ZAxisTestsScreenView& v
) :
    view(v) {}

void ZAxisTestsScreenPresenter::activate() {}

void ZAxisTestsScreenPresenter::deactivate() {}

void ZAxisTestsScreenPresenter::handleZAxisTestTaskFinish(
    ATC::ZAxisTestResults results
) {
    view.showTestResults(results);
}

void ZAxisTestsScreenPresenter::startButtonPressed() {
    model->startZAxisTestTask();
}

void ZAxisTestsScreenPresenter::cancelButtonPressed() {
    model->cancelCurrentTask();
}