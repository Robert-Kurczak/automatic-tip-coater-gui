#include <gui/startscreen_screen/StartScreenPresenter.hpp>
#include <gui/startscreen_screen/StartScreenView.hpp>

StartScreenPresenter::StartScreenPresenter(StartScreenView& v) :
    view(v) {}

void StartScreenPresenter::activate() {
    coatingTask = &model->getSystemApi().tasks.coatingTask;
}

void StartScreenPresenter::deactivate() {}

void StartScreenPresenter::handleCoatingTaskFinish(bool wasSuccessful) {
    view.resetFooterButtons();
}

void StartScreenPresenter::startButtonPressed() {
    coatingTask->schedule();
}

void StartScreenPresenter::cancelButtonPressed() {
    model->getSystemApi().tasks.taskControl.cancelAll();
}