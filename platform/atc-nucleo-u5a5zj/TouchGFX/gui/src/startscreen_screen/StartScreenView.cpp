#include <gui/startscreen_screen/StartScreenView.hpp>

StartScreenView::StartScreenView() {}

void StartScreenView::setupScreen() {
    StartScreenViewBase::setupScreen();
}

void StartScreenView::tearDownScreen() {
    StartScreenViewBase::tearDownScreen();
}

void StartScreenView::startCoating() {
    presenter->startButtonPressed();
}

void StartScreenView::cancelCoating() {
    presenter->cancelButtonPressed();
}

void StartScreenView::resetFooterButtons() {
    startCancelFooter.resetState();
}
