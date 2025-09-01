#include <gui/spindletestsscreen_screen/SpindleTestsScreenPresenter.hpp>
#include <gui/spindletestsscreen_screen/SpindleTestsScreenView.hpp>

SpindleTestsScreenPresenter::SpindleTestsScreenPresenter(
    SpindleTestsScreenView& v
) :
    view(v) {}

void SpindleTestsScreenPresenter::activate() {}

void SpindleTestsScreenPresenter::deactivate() {}

void SpindleTestsScreenPresenter::handleSpindleTestTaskFinish(
    ATC::SpindleTestResults results
) {
    view.resetFooterButtons();
    view.showTestResults(results);
}

void SpindleTestsScreenPresenter::startButtonPressed() {
    ATC::IConsumableTaskService<ATC::SpindleTestResults>&
        spindleTestTask = model->getSystemApi().tasks.spindleTestTask;

    spindleTestTask.schedule();
}

void SpindleTestsScreenPresenter::cancelButtonPressed() {
    ATC::ITaskControlService& taskControl =
        model->getSystemApi().tasks.taskControl;

    taskControl.cancelAll();
}