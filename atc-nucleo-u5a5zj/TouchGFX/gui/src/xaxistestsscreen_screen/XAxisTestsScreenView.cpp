#include <gui/xaxistestsscreen_screen/XAxisTestsScreenView.hpp>

XAxisTestsScreenView::XAxisTestsScreenView() {}

void XAxisTestsScreenView::setupScreen() {
    XAxisTestsScreenViewBase::setupScreen();
}

void XAxisTestsScreenView::tearDownScreen() {
    XAxisTestsScreenViewBase::tearDownScreen();
}

void XAxisTestsScreenView::startTest() {
    axisTestsResults.setLoadingIcons();

    presenter->startButtonPressed();
}

void XAxisTestsScreenView::cancelTest() {
    axisTestsResults.setStartLimitSwitchError();
    axisTestsResults.setEndLimitSwitchError();
    axisTestsResults.setMotorDriverError();

    presenter->cancelButtonPressed();
}