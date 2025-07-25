#include <gui/xaxistestsscreen_screen/XAxisTestsScreenView.hpp>

// TODO change "Tests" to "Test"
XAxisTestsScreenView::XAxisTestsScreenView() {}

void XAxisTestsScreenView::setupScreen() {
    XAxisTestsScreenViewBase::setupScreen();
}

void XAxisTestsScreenView::tearDownScreen() {
    XAxisTestsScreenViewBase::tearDownScreen();
}

void XAxisTestsScreenView::showTestResults(
    ATC::XAxisTestResults results
) {
    if (results.startLimitSwitchSuccess) {
        axisTestsResults.setStartLimitSwitchSuccess();
    } else {
        axisTestsResults.setStartLimitSwitchError();
    }

    if (results.endLimitSwitchSuccess) {
        axisTestsResults.setEndLimitSwitchSuccess();
    } else {
        axisTestsResults.setEndLimitSwitchError();
    }

    if (results.motorDriverSuccess) {
        axisTestsResults.setMotorDriverSuccess();
    } else {
        axisTestsResults.setMotorDriverError();
    }
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