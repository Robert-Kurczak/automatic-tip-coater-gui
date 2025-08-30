#include <gui/rotationtestsscreen_screen/RotationTestsScreenPresenter.hpp>
#include <gui/rotationtestsscreen_screen/RotationTestsScreenView.hpp>

RotationTestsScreenPresenter::RotationTestsScreenPresenter(
    RotationTestsScreenView& v
) :
    view(v) {}

void RotationTestsScreenPresenter::activate() {
    spindleTestTask = &model->getSystemApi().tasks.spindleTestTask;
}

void RotationTestsScreenPresenter::deactivate() {}

void RotationTestsScreenPresenter::handleRotatorTestTaskFinish(
    ATC::SpindleTestResults results
) {
    view.resetFooterButtons();
    view.showTestResults(results);
}

void RotationTestsScreenPresenter::startButtonPressed() {
    spindleTestTask->schedule();
}

void RotationTestsScreenPresenter::cancelButtonPressed() {
    model->getSystemApi().tasks.taskControl.cancelAll();
}
