#include <gui/rotationtestsscreen_screen/RotationTestsScreenPresenter.hpp>
#include <gui/rotationtestsscreen_screen/RotationTestsScreenView.hpp>

RotationTestsScreenPresenter::RotationTestsScreenPresenter(
    RotationTestsScreenView& v
) :
    view(v) {}

void RotationTestsScreenPresenter::activate() {}

void RotationTestsScreenPresenter::deactivate() {}

void RotationTestsScreenPresenter::handleRotatorTestTaskFinish(
    ATC::RotatorTestResults results
) {
    view.resetFooterButtons();
    view.showTestResults(results);
}

void RotationTestsScreenPresenter::startButtonPressed() {
    model->startRotationTestTask();
}

void RotationTestsScreenPresenter::cancelButtonPressed() {
    model->cancelCurrentTask();
}