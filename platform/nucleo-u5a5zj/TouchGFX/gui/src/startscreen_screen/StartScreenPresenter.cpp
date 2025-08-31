#include <gui/startscreen_screen/StartScreenPresenter.hpp>
#include <gui/startscreen_screen/StartScreenView.hpp>

StartScreenPresenter::StartScreenPresenter(StartScreenView& v) :
    view(v) {}

void StartScreenPresenter::activate() {}

void StartScreenPresenter::deactivate() {}

void StartScreenPresenter::handleCoatingTaskFinish(bool wasSuccessful) {
    view.resetFooterButtons();
}

void StartScreenPresenter::startButtonPressed() {
    ATC::IConsumableTaskService<bool>& coatingTask =
        model->getSystemApi().tasks.coatingTask;

    coatingTask.schedule();
}

void StartScreenPresenter::cancelButtonPressed() {
    ATC::ITaskControlService& taskControl =
        model->getSystemApi().tasks.taskControl;

    taskControl.cancelAll();
}