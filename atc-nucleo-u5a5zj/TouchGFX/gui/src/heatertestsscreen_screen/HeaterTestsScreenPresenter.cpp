#include <gui/heatertestsscreen_screen/HeaterTestsScreenPresenter.hpp>
#include <gui/heatertestsscreen_screen/HeaterTestsScreenView.hpp>

HeaterTestsScreenPresenter::HeaterTestsScreenPresenter(
    HeaterTestsScreenView& v
) :
    view(v) {}

void HeaterTestsScreenPresenter::activate() {}

void HeaterTestsScreenPresenter::deactivate() {}

void HeaterTestsScreenPresenter::handleHeaterTestTaskFinish(
    ATC::HeaterTestResults results
) {
    view.resetFooterButtons();
    view.showTestResults(results);
}

void HeaterTestsScreenPresenter::startButtonPressed() {
    model->startHeaterTestTask();
}

void HeaterTestsScreenPresenter::cancelButtonPressed() {
    model->cancelCurrentTask();
}