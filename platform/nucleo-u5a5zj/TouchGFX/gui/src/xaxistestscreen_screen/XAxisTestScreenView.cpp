#include <gui/xaxistestscreen_screen/XAxisTestScreenView.hpp>

XAxisTestScreenView::XAxisTestScreenView() {}

void XAxisTestScreenView::setupScreen() {
    XAxisTestScreenViewBase::setupScreen();
}

void XAxisTestScreenView::tearDownScreen() {
    XAxisTestScreenViewBase::tearDownScreen();
}

void XAxisTestScreenView::resetFooterButtons() {
    startCancelFooter.resetState();
}

void XAxisTestScreenView::showTestResults(ATC::AxisTestResults results) {
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

void XAxisTestScreenView::startTest() {
    axisTestsResults.setLoadingIcons();

    presenter->startButtonPressed();
}

void XAxisTestScreenView::cancelTest() {
    axisTestsResults.setStartLimitSwitchError();
    axisTestsResults.setEndLimitSwitchError();
    axisTestsResults.setMotorDriverError();

    presenter->cancelButtonPressed();
}