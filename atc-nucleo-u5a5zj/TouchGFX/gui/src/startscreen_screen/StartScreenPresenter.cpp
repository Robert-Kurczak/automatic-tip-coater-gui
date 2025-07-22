#include <gui/startscreen_screen/StartScreenPresenter.hpp>
#include <gui/startscreen_screen/StartScreenView.hpp>

StartScreenPresenter::StartScreenPresenter(StartScreenView& v) :
    view(v) {}

void StartScreenPresenter::activate() {}

void StartScreenPresenter::deactivate() {}

void StartScreenPresenter::startButtonPressed() {
    model->startCoatingTask();
}

void StartScreenPresenter::cancelButtonPressed() {
    model->cancelCurrentTask();
}