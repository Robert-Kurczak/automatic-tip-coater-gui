#include <gui/xaxistestsscreen_screen/XAxisTestsScreenPresenter.hpp>
#include <gui/xaxistestsscreen_screen/XAxisTestsScreenView.hpp>

XAxisTestsScreenPresenter::XAxisTestsScreenPresenter(
    XAxisTestsScreenView& v
) :
    view(v) {}

void XAxisTestsScreenPresenter::activate() {}

void XAxisTestsScreenPresenter::deactivate() {}

void XAxisTestsScreenPresenter::startButtonPressed() {
    model->startXAxisTestTask();
}

void XAxisTestsScreenPresenter::cancelButtonPressed() {
    model->cancelCurrentTask();
}