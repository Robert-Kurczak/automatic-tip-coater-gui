#include <gui/heatertestsscreen_screen/HeaterTestsScreenPresenter.hpp>
#include <gui/heatertestsscreen_screen/HeaterTestsScreenView.hpp>

HeaterTestsScreenPresenter::HeaterTestsScreenPresenter(
    HeaterTestsScreenView& v
) :
    view(v) {}

void HeaterTestsScreenPresenter::activate() {}

void HeaterTestsScreenPresenter::deactivate() {}

void HeaterTestsScreenPresenter::startButtonPressed() {
    model->testHeater();
}

void HeaterTestsScreenPresenter::cancelButtonPressed() {
    model->cancelCurrentTask();
}