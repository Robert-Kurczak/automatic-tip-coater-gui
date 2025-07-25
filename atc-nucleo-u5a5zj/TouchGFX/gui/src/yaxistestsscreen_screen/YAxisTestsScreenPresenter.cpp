#include <gui/yaxistestsscreen_screen/YAxisTestsScreenPresenter.hpp>
#include <gui/yaxistestsscreen_screen/YAxisTestsScreenView.hpp>

YAxisTestsScreenPresenter::YAxisTestsScreenPresenter(
    YAxisTestsScreenView& v
) :
    view(v) {}

void YAxisTestsScreenPresenter::activate() {}

void YAxisTestsScreenPresenter::deactivate() {}

void YAxisTestsScreenPresenter::handleYAxisTestTaskFinish(
    ATC::YAxisTestResults results
) {
    view.showTestResults(results);
}

void YAxisTestsScreenPresenter::startButtonPressed() {
    model->startYAxisTestTask();
}

void YAxisTestsScreenPresenter::cancelButtonPressed() {
    model->cancelCurrentTask();
}